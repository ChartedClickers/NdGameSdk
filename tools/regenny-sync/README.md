Regenny Sync Tool

Purpose: Keep the shared SDK regenny data up to date from your working copies for multiple game versions (e.g., t2r, t1x).

What it does
- Copies everything from `researching/regenny-sdk/<game>/regenny` into `shared/NdGameSdk/regenny/<game>`.
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
    - `--src <path>` default: `researching/regenny-sdk`
    - `--dst <path>` default: `shared/NdGameSdk/regenny`

Notes
- Safe to re-run; combine with `--yes` for automation.
- Creates destination folders if missing.
- Source layout expected:
  - `researching/regenny-sdk/t2r/regenny/...`
  - `researching/regenny-sdk/t1x/regenny/...`

