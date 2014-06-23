# Vision ANT Tasks

The following Vision ANT Tasks can be made available to an ANT build script by including the task definitions specified in the `VisionAntTasks.jar` 

```xml

	<!-- adding the Vision ANT Tasks task definitions -->
	<taskdef resource="com/havok/Vision/anttasks/visionanttasks.properties">
		<classpath>
		  <pathelement location="ant/VisionAntTasks/VisionAntTasks.jar"/>
		</classpath>
	</taskdef>  
```

## VisionCopyLib

Copies an native library (.so) file into a the correct sub-folder for the processor architecture and removes any unneeded symbols from the file to reduce the size. It will also prefix the library with "lib" if it does not have that prefix already.

**Parameters:**

* `Arch` - REQUIRED - x86, arm or armv7  
* `Lib` - REQUIRED - The path to the .so file to be copied
* `ToDir`- REQUIRED - The path to the folder where the .so will be copied to (and placed in an the appropriate architecture sub-folder)
* `Strip` - OPTIONAL - true or false. true to strip unneeded symbols, false to leave as is/>

**Example:**

This example will copy `d:/files/mygame/bin/x86/MyGame.so` to `d:/output/libs/x86/libMyGame.so` and also remove any unneeded symbols from  `libMyGame.so`

```xml
   
	<VisionCopyLib 
	  Arch="x86" 
	  Lib="d:/files/mygame/bin/MyGame.so"
	  ToDir="d:/output/libs"
	  Strip="true"/>
```

## VisionCopyAssets

Copies assets from one folder to another. Is aware of the Vision asset management system and will try to exclude files that are not relevant to the android profile (if one is found in `AssetMgmt_data/android.aidlt` ).

**Parameters:**

* `DestinationPath` - REQUIRED - The path to a folder where the assets will be copied
* `fileset` - REQUIRED - A source folder to be copied. You can use the excludes to omit any custom folders or files (see [ANT FileSet Type](http://ant.apache.org/manual/Types/fileset.html))

**Example 1:**

Will copy the assets contained in `./assets/Assets` from `../../../../Assets/` while excluding the Vision asset management data thumbnails folder.  `./assets/Assets` folders will be created if they don't exist.

```xml

	<VisionCopyAssets DestinationPath="./assets/Assets">
	  <fileset dir="../../../../Assets/">
	    <include name="**"/>
	    <exclude name="**/AssetMgmt_data/thumbnails/*"/>
	  </fileset>
	</VisionCopyAssets>

```

**Example 2:**

Will copy the assets contained in `./assets/Data/Vision/Base` from `../../../../Data/Vision/Base` while excluding the Vision asset management data thumbnails folder. `./assets/Data/Vision/Base` folders will be created if they don't exist.

```xml

    <VisionCopyAssets DestinationPath="./assets/Data/Vision/Base">
      <fileset dir="../../../../Data/Vision/Base">
        <include name="**"/>
        <exclude name="**/AssetMgmt_data/thumbnails/*"/>
      </fileset>
    </VisionCopyAssets>

```

## VisionCopyGdbserver

Copies the native gdbserver file from the Android NDK into the folder that is used for debugging on the device.

**Parameters:**

* `Arch` - REQUIRED - x86, arm or armv7  
* `ToDir`- REQUIRED - The path to the folder where the gdbserver will be copied to (and placed in an the appropriate architecture sub-folder)

**Example:**

This example will copy the x86 gdbserver to `d:/output/libs/x86/gdbserver`

```xml
   
	<VisionCopyLib Arch="x86" ToDir="d:/output/libs"/>
```

## VisionVFileServe

Generates and copies the vFileServe.txt data to connected Android devices.

**Parameters**

* `ip` - OPTIONAL - the network ip address of the host machine to load files from (defaults to first system IP found)
* `port` - OPTIONAL - the network port of the host machine to load files from (defaults to 4225)
* `device` - OPTIONAL - nested attribute to specify the name of the device(s) to copy to, can be used muliple times


**Example 1:**

Generates the vFileServe.txt with default IP and Port and copies it to the first device detected by adb.exe

```xml

	<VisionVFileServe/>
```

**Example 2**

Generates the vFileServe.txt with an ip of `192.168.0.1` and port `9998` and copies it to the 2 devices specified.

```xml

	<VisionVFileServe ip="192.168.0.1" port="9998">
		<device name="TA74405TXW"/>
		<device name="WXT50447AT"/>
	</VisionVFileServe>
```

## VisionInstallApk

Installs a `.apk` file onto an android device or device(s).

**Parameters**

* `apk` - REQUIRED - the filename of the .apk to be installed
* `timeout` - OPTIONAL - the time in seconds to wait for the .apk install process to finish
* `device` - OPTIONAL - nested attribute to specify the name of the device(s) to copy to, can be used muliple times


**Example 1:**

Installs the `mygame.apk` file onto the first device found by adb.exe, the default timeout will be 1200 seconds.
If no devices are found to be attached to the host then installation is skipped.

```xml

	<VisionInstallApk apk="./mygame/mygame.apk" />
```

**Example 2**

Installs the `mygame.apk` file onto the 2 android devices specified and waits no longer than 60 seconds for each install to complete.

```xml

	<VisionInstallApk apk="./mygame/mygame.apk" timeout="60">
		<device name="TA74405TXW"/>
		<device name="WXT50447AT"/>
	</VisionInstallApk>
```


## VisionStripLib

Strips all unneeded symbols from the native library (.so) to reduce size and obfuscate file. This will overwrite the input library file.
 
**Parameters:**

* `Arch` - REQUIRED - x86, arm or armv7  
* `Lib` - REQUIRED - The path to the .so file to be stripped

**Example**

Removes any unneeded symbols from `MyGame.so`, overwriting `MyGame.so` with the output.

```xml

	<VisionStripLib Arch="x86" Lib="d:/files/mygame/bin/MyGame.so">
```
