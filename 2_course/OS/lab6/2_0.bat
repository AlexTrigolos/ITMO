echo %computername%
cd\
md temp
net share temp=C:\temp

echo for %%%%B in (C:\Windows\*) do if %%%%~zB GEQ 2097152 xcopy /Z %%%%B C:\temp > 2_0_2.bat

timeout /T 60
call %~dp02_0_2.bat