import os

step = 0x20000
base_addr = 0x80400000
linker = "src/linker.ld"

app_id = 0
apps = os.listdir("build/app")
apps.sort()

for app in apps:
    app = app[: app.find(".")]
    os.system(
        "cargo rustc --bin %s --release -- -Clink-args=-Ttext=%x"               # 对每一个应用程序进行编译
        % (app, base_addr + step * app_id)
    )
    print(
        "[build.py] application number is %s"
        % (app_id + 1)
    )
    print(
        "[build.py] application %s start with address %s"
        % (app, hex(base_addr + step * app_id))
    )
    # app_id = app_id + 1
