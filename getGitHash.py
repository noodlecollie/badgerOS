import subprocess

revision = subprocess.check_output(["git", "rev-parse", "--short", "HEAD"]).strip()
print(f'-DBUILD_HASH={revision}')
