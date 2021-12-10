# that game engine

Contains the source code for the SFML game engine tutorial series, hosted on thatgamesguy.co.uk. Find the first tutorial at https://thatgamesguy.co.uk/game-engine-dev/

Important
The code is cross-platform and will compile on Windows, MacOS, and Linux. However if you are building for MacOS then there are a couple of additional steps you need to do before it will compile.

Add compiler flag 'MACOS' in XCode:
1. Click on the game engine project in the sidebar.
2. Click on Build Settings on the top row.
3. In the search bar type “custom compiler flag”.
4 In “Other C Flags” enter “-D MACOS”. The Other C++ Flags field will be automatically populated.

Link to the CoreFoundation framework in XCode:
1. Click on the game engine project in the sidebar.
2. Click on the General tab. 
3. Find a section called ‘Linked Frameworks and Libraries’.
4. Click on the plus sign.
5. Locate CoreFroundation.framework.
6. Click Add.

If you are bulding on MacOS but not in XCode then you will need to follow a different procedure.
