set BUILD_TYPE=%1
echo BUILD_TYPE: %BUILD_TYPE%

conan install . ^
    --settings build_type=%BUILD_TYPE% ^
    --install-folder build/%BUILD_TYPE%/modules ^
    --build missing