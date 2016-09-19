This is nearly the most significant project I carried out in my undergraduate years.
I did it for practice of the knowledge I learned in the book "Windows Via C/C++" by Jeffrey Richter. Book reading and programming together took me about one year.

This project was essentially an external program working along with Warcraft III v1.20e by Blizzard. Initially my goal was to use my program to read the number of golds held by an computer AI rival in an player-versus-AI local battle, and display the gold value inside the game application. After several tries I found I couldn't make the gold value show inside the game application by intercepting some DirectX APIs, so I switched to display the number using the external program.
However, I wrote this program not only for achieving the above goal, but also for practically using the techniques described in the book as many as possible.

Many years have passed, so I could hardly remember the details, nor can I guarantee the accuracy of the impression of it which I have for now. I even have forgotten how MFC works. The following is roughly the things I remember:

1. MFCApplication1 (I did not bother to give this program a name) launches and detect the status of war3.exe. If successive, inject Win32DLL1.dll (a subproject creating a dynamic-link lib, not given a name either) into the memory space of war3.exe.

2. On injection of Win32DLL1.dll, it will launch a new thread within process war3.exe, which create a memory File Mapping and MapViewOfFile in order to share one same commited page with MFCApplication1.exe. I did this to make war3.exe (with Win32DALL1.dll injected) to share a value with MFCApplication1.exe directly through memory.

3. Synchronization between the two processes was done by both Windows kernel objects and Window Messages.

4. After injecting Win32DLL1.dll to war3.exe, MFCApplication1 will use the process handle of war3.exe to forcibly change a little bit of the original code. I wrote some very simple assembly code, which would fetch the gold value I wanted and copied it into another memory address I specified, and I used a tool to transform the assembly code into machine code. How could I know the memory address of the original code that I wanted to modify? Cheat Engine helped. In this case, I could not simply find a stable memory address that stored the gold value, so it was why I changed the code of a running process. C pointer an API called WriteProcessMemory(...) is such a powerful tool that can do this.

Note: I tried API Interception using Detour Library to display the gold value but faild, but the related code can remain in this project.


Even myself cannot compile it now due to lack of libraries like Detour, and no Warcraft III is on my Windows now.