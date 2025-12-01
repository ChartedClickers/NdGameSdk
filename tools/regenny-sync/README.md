Regenny Sync Tool

Purpose: Keep the shared SDK regenny data up to date from your working copies for multiple game versions (e.g., t2r, t1x).

What it does
- Copies everything from `forge/regenny-sdk/<game>/regenny` into `src/components/NdGameSdk/regenny/<game>`.
- Cleans the destination folder contents before copying (replace-in-place) unless `--no-clean` is provided.
- Supports multiple games in one run via auto-discovery or `--game` flags.
- Offers `--dry-run` to preview and `--yes` to skip confirmation.

Usage
- From the repo root, run:
  - `python tools/regenny-sync/update_regenny.py --yes`
  - Preview only: `python tools/regenny-sync/update_regenny.py --dry-run`
  - Specific game(s): `python tools/regenny-sync/update_regenny.py -g t2r -g t1x --yes`
  - List discovered games: `python tools/regenny-sync/update_regenny.py --list`
  - Merge without cleaning: `python tools/regenny-sync/update_regenny.py --no-clean --yes`
  - Override paths:
    - `--src <path>` default: `forge/regenny-sdk`
    - `--dst <path>` default: `src/components/NdGameSdk/regenny`

Notes
- Safe to re-run; combine with `--yes` for automation.
- Creates destination folders if missing.
- Source layout expected:
  - `forge/regenny-sdk/t2r/regenny/...`
  - `forge/regenny-sdk/t1x/regenny/...`
