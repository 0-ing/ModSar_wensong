# --------------------------------------------------------------------------
# Copyright (c) Robert Bosch GmbH, 2017. All rights reserved.
# The reproduction, distribution and utilization of this document as well as the communication of its contents to
# others without explicit authorization is prohibited. Offenders will be held liable for the payment of damages.
# All rights reserved in the event of the grant of a patent, utility model or design.
# --------------------------------------------------------------------------

############################################
# Set configuration parameters
############################################

set(PROXIES
    "com/bosch/vrte/method/method")

set(SKELETONS
    "com/bosch/vrte/method/method")

set(DSOMEIP_FILES_FS1
    "Machine_IT_UsrDoc_FS1_someip.json")

set(DSOMEIP_FILES_FS2
    "Machine_IT_UsrDoc_FS2_someip.json")

set(ARXML_FILES
    "${ARA_HEADER}/Apps_IT_UsrDocMethod.arxml"
    "${SW_CLUSTER_DUMMY_ARXML}"
    "${MACHINE_DEFINITION_FS1_ARXML}"
    "${MACHINE_DEFINITION_FS2_ARXML}"
    "${ARA_HEADER}/Method.arxml"
    "${ARA_HEADER}/ServiceInstanceAndMachineMapping.arxml")


############################################
# Call helper function for add & install
############################################

setup_int_test_gen()
