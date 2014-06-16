REM use this to generate a release key for your game
REM add your ant.properties file and specify the name/alias/passwords for the key you create for release
REM
REM e.g.
REM key.store=my-release-key.keystore
REM key.alias=cloudconnection
REM key.store.password=cloudconnection
REM	key.alias.password=cloudconnection
REM 

keytool -genkey -v -keystore my-release-key.keystore -alias alias_name -keyalg RSA -keysize 2048 -validity 10000

