cd\
md LAB6
cd LAB6
wmic os get Caption > Caption.txt
wmic os get FreePhysicalMemory > FreePhysicalMemory.txt
wmic os get TotalVisibleMemorySize > TotalVisibleMemorySize.txt
wmic logicaldisk get name, description > Description.txt

md TEST
xcopy C:\LAB6 C:\LAB6\TEST
cd TEST

copy /y /B C:\LAB6\* C:\LAB6\TEST\AllFiles.txt

for /f "skip=1" %%i in ('dir /b/a-d/o-d/t:c') do del %%i