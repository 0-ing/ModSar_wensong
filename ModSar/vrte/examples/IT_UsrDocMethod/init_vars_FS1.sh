echo "Initializing variables"
export LD_LIBRARY_PATH=/opt/vrte/lib:$LD_LIBRARY_PATH
export PATH=/opt/vrte/bin:/opt/testapps:$PATH
export DSOMEIP_CONFIGURATION=/opt/testapps/config/Machine_IT_UsrDoc_FS1_someip.json
export ECUCFG_ENV_VAR_ROOTFOLDER=/opt/vrte/etc/config
echo LD_LIBRARY_PATH is $LD_LIBRARY_PATH
echo PATH is $PATH
echo DSOMEIP_CONFIGURATION is $DSOMEIP_CONFIGURATION
echo ECUCFG_ENV_VAR_ROOTFOLDER is $ECUCFG_ENV_VAR_ROOTFOLDER

echo
echo "Due to windows built tars also do chmod +x on binaries"
find /opt/vrte/bin -maxdepth 1 -type f
find /opt/vrte/bin -maxdepth 1 -type f -exec chmod +x {}
find /opt/testapps -maxdepth 1 -type f
find /opt/testapps -maxdepth 1 -type f -exec chmod +x {}

