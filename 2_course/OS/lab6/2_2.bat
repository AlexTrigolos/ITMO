fc /b C:\Windows\%1 \\%COMPUTERNAME%\temp\%1 > nul

if %ERRORLEVEL% == 1 (
	echo "Files are not same"
) else (
	echo "Files are same"
)