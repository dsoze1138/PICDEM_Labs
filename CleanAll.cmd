@dir /aD /b /s | findstr /r /i \.[8,X]$ > CleanAllList.txt
@FOR /F  %%i IN (CleanAllList.txt) DO @call CleanDir.cmd %%i NoPause
@if exist CleanAllList.txt   del   /f /q CleanAllList.txt
@pause
