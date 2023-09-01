# --------------------------------------------------------------------------
# Copyright (c) Robert Bosch GmbH, 2020. All rights reserved.
# The reproduction, distribution and utilization of this document as well as the communication of its contents to
# others without explicit authorization is prohibited. Offenders will be held liable for the payment of damages.
# All rights reserved in the event of the grant of a patent, utility model or design.
# --------------------------------------------------------------------------

#setup_int_test_base()

if(${WAVE3_VARIANT} STREQUAL "WAVE3.3_P")
add_subdirectory(publisher)
elseif(${WAVE3_VARIANT} STREQUAL "WAVE3.3_S")
add_subdirectory(subscriber)
endif()
#add_subdirectory(cfg)
