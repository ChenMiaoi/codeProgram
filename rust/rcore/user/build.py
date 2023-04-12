import os

step = 0x20000
base_addr = 0x80400000
linker = "src/linker.ld"

apps = os.listdir("build/app")
apps.sort()

for app in apps:
    app = app[: app.find(".")]
    os.system(
        "cargo rustc --bin %s --release -- -Clink-args=-Ttext=%x"
        % (app, base_addr + step)
    )
    print(
        "[build.py] application %s start with address %s"
        % (app, hex(base_addr + step))
    )
