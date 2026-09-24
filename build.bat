:: Builds the App
call gradlew.bat assembleDebug

:: Installs the App
adb install -r app\build\outputs\apk\debug\app-debug.apk

:: Opens the App
adb shell am start -n "com.raylib.raymob/.NativeLoader"