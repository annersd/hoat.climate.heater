Import("env")
env.Replace( MKSPIFFSTOOL=env.get("PROJECT_DIR") + '/tools/mklittlefs' )  # PlatformIO now believes it has actually created a SPIFFS
