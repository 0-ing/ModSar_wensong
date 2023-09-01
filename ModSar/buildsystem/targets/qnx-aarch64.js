console.log("start");


download([
    {name:"boost_1_55",url:"http://xx"},
    {name:"vsomeip_1_33",url:"http://xxx"}
]);

fileCopy([
    {src:"src/qnx_patch.file",dest:"boost_1_55"}
]);


action("source","qnx_env"); // cmd name and arguments
action("git patch",{patch:"boot_1_55.patch",dest:"boost_1_55"});
action("cmake",{dest:"boost_1_55"});

runCmd([

]);

runCmd([

]);