out echo "Clearing data..."
rm hdd:/tests/*
rm hdd:/pgui/*
rm hdd:/gui/*
out echo "Installing packages..."
out package install hdd:/tests.pkf hdd:/tests
out package install hdd:/protogui.pkf hdd:/pgui
out package install hdd:/gui.pkf hdd:/gui
out echo "Done".
out termctl pointer-speed set 3000000
