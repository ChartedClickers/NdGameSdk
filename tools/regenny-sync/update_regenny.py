#!/usr/bin/env python3
from __future__ import annotations

import argparse
import os
from pathlib import Path
import shutil
import sys

def researching_root() -> Path:
    """
    Resolve the path to the 'researching' folder based on the current layout:
      <repo>/tools/regenny-sync/update_regenny.py

    Returns: <repo>/researching
    """
    here = Path(__file__).resolve()
    repo_root = here.parents[2]  # .../NdGameSdk
    return repo_root / "researching"


def discover_games(src_base: Path) -> list[str]:
    games: list[str] = []
    if not src_base.exists():
        return games
    for child in src_base.iterdir():
        if child.is_dir() and (child / "regenny").is_dir():
            games.append(child.name)
    games.sort()
    return games


def confirm(prompt: str) -> bool:
    try:
        resp = input(f"{prompt} [y/N]: ").strip().lower()
    except EOFError:
        return False
    return resp in {"y", "yes"}


def clean_directory(path: Path, *, dry_run: bool, verbose: bool) -> None:
    if not path.exists():
        return
    for entry in path.iterdir():
        if dry_run:
            print(f"DRY-RUN delete: {entry}")
            continue
        if entry.is_dir() and not entry.is_symlink():
            shutil.rmtree(entry)
            if verbose:
                print(f"Deleted directory: {entry}")
        else:
            try:
                entry.unlink()
            except FileNotFoundError:
                pass
            if verbose:
                print(f"Deleted file: {entry}")


def copy_tree(src: Path, dst: Path, *, dry_run: bool, verbose: bool) -> None:
    for root, dirs, files in os.walk(src):
        rel = Path(root).relative_to(src)
        target_dir = dst / rel
        if not dry_run:
            target_dir.mkdir(parents=True, exist_ok=True)
        if verbose:
            print(f"Ensure dir: {target_dir}")
        for d in dirs:
            td = target_dir / d
            if not dry_run:
                td.mkdir(parents=True, exist_ok=True)
            if verbose:
                print(f"Ensure dir: {td}")
        for f in files:
            sfile = Path(root) / f
            tfile = target_dir / f
            if dry_run:
                print(f"DRY-RUN copy: {sfile} -> {tfile}")
            else:
                shutil.copy2(sfile, tfile)
                if verbose:
                    print(f"Copied: {sfile} -> {tfile}")


def run_sync(
    *,
    src_base: Path,
    dst_base: Path,
    games: list[str],
    clean: bool,
    dry_run: bool,
    yes: bool,
    verbose: bool,
) -> int:
    if not games:
        print("No game versions found to sync.")
        return 1

    print("Regenny sync plan:")
    for g in games:
        src = src_base / g / "regenny"
        dst = dst_base / g
        print(f" - {g}: {src} -> {dst} (clean={clean})")

    if not yes:
        if not confirm("Proceed with the above operations?"):
            print("Aborted by user.")
            return 130

    rc = 0
    for g in games:
        src = src_base / g / "regenny"
        dst = dst_base / g

        if not src.exists():
            print(f"WARN: Missing source for {g}: {src}")
            rc = 2
            continue

        if dry_run:
            print(f"DRY-RUN ensure destination: {dst}")
        else:
            dst.mkdir(parents=True, exist_ok=True)

        if clean:
            clean_directory(dst, dry_run=dry_run, verbose=verbose)

        copy_tree(src, dst, dry_run=dry_run, verbose=verbose)

    return rc


def main(argv: list[str]) -> int:
    researching = researching_root()
    default_src = researching / "regenny-sdk"
    default_dst = researching.parent / "shared" / "NdGameSdk" / "regenny"

    parser = argparse.ArgumentParser(
        description=(
            "Sync regenny data from researching/regenny-sdk/<game>/regenny "
            "into shared/NdGameSdk/regenny/<game>."
        )
    )
    parser.add_argument(
        "--src",
        type=Path,
        default=default_src,
        help=f"Source base folder (default: {default_src})",
    )
    parser.add_argument(
        "--dst",
        type=Path,
        default=default_dst,
        help=f"Destination base folder (default: {default_dst})",
    )
    parser.add_argument(
        "--game",
        "-g",
        action="append",
        help=(
            "Game key to sync (e.g. t2r, t1x). "
            "May be provided multiple times. If omitted, auto-discovers all."
        ),
    )
    parser.add_argument(
        "--list",
        action="store_true",
        help="List discovered games and exit.",
    )
    parser.add_argument(
        "--dry-run",
        action="store_true",
        help="Preview actions without changing files.",
    )
    parser.add_argument(
        "--no-clean",
        dest="clean",
        action="store_false",
        help="Do not remove existing destination files before copying.",
    )
    parser.add_argument(
        "--yes",
        "-y",
        action="store_true",
        help="Do not prompt for confirmation.",
    )
    parser.add_argument(
        "--verbose",
        "-v",
        action="store_true",
        help="Print detailed actions.",
    )
    parser.set_defaults(clean=True)

    args = parser.parse_args(argv)

    src_base = args.src.resolve()
    dst_base = args.dst.resolve()

    games = args.game if args.game else discover_games(src_base)

    if args.list:
        found = discover_games(src_base)
        if not found:
            print(f"No games found under {src_base}")
            return 0
        print("Discovered games:")
        for g in found:
            print(f" - {g}")
        return 0

    return run_sync(
        src_base=src_base,
        dst_base=dst_base,
        games=games,
        clean=args.clean,
        dry_run=args.dry_run,
        yes=args.yes,
        verbose=args.verbose,
    )


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))

