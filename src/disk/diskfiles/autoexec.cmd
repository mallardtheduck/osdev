out echo "Clearing data..."
rm hdd:/tests/*
rm hdd:/pgui/*
out echo "Installing packages..."
out package install hdd:/tests.pkf hdd:/tests
out package install hdd:/protogui.pkf hdd:/pgui
out echo "Done".
out termctl pointer-speed set 3000000
