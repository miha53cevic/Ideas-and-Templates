# Install Flutter withouth Android Studio
Last updated: 20.8.2023.

# Prerequisites
- [Flutter](https://docs.flutter.dev/get-started/install)
- [Android Command Line Tools Only](https://developer.android.com/studio)

# Instructions
### Step 1
Create /android folder

### Step 2
Extract flutter into it /android/flutter

### Step 3
Extract command-line-tools /android/cmdline-tools/latest

### Step 4
Add environment variables for flutter/bin and cmdline-tools/latest/bin

### Step 5
Run sdkmanager.bat --list

### Step 6 
Install platform-tools, platforms;android**PlatformVersion** and build-tools;**PlatformVersion**\
```bash
sdkmanager.bat "platform-tools" "platforms;android-33" "build-tools;33.0.2"
```

### Step 7
Set enviroment variable ANDROID_HOME to /android location
```bash
flutter config --android-sdk "pathTo/android"
```

### Step 8
Accept licenses
```bash
flutter doctor --android-licenses 
```

### Step 9
Check if everything good
```bash
flutter doctor -v
```

### Extra
[Outdated but maybe useful guide](https://ksrk.medium.com/install-flutter-without-android-studio-on-window-9d3781172912)