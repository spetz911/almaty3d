#import <OpenGL/gl.h>
#import <Cocoa/Cocoa.h>

//clang tryCocoa.m -framework OpenGL -framework Cocoa

@interface MyOpenGLView : NSOpenGLView

@end


@implementation MyOpenGLView

- (void)prepareOpenGL {
	printf("success!\n");
    // Synchronize buffer swaps with vertical refresh rate
    GLint swapInt = 1;
    [[self openGLContext] setValues:&swapInt forParameter:NSOpenGLCPSwapInterval];
}


- (void)drawRect: (NSRect)dirtyRect {
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glFlush();
    [self setNeedsDisplay:YES];
}


@end




int main(int argc, char *argv[])
{
    [NSAutoreleasePool new];
    [NSApplication sharedApplication];

// + NSApplicationActivationPolicyRegular
// The application is an ordinary app that appears in the Dock and may have a user interface. This is the default for bundled apps, unless overridden in the Info.plist.
// + NSApplicationActivationPolicyAccessory
// The application does not appear in the Dock and does not have a menu bar, but it may be activated programmatically or by clicking on one of its windows. This corresponds to value of the LSUIElement key in the application’s Info.plist being 1.
// + NSApplicationActivationPolicyProhibited
// The application does not appear in the Dock and may not create windows or be activated. This corresponds to the value of the LSBackgroundOnly key in the application’s Info.plist being 1. This is also the default for unbundled executables that do not have Info.plists.
    [NSApp setActivationPolicy:NSApplicationActivationPolicyRegular];

    NSRect frameSize = NSMakeRect(0, 0, 1200, 800);

    id window = [[[NSWindow alloc]
    	initWithContentRect:frameSize
        styleMask:NSTitledWindowMask
        backing:NSBackingStoreBuffered
        defer:NO]
            autorelease];
    id appName = @"TROROLOLO APPLICAION";
    [window setTitle:appName];
    // Positions the window's top left to a given point.
    [window cascadeTopLeftFromPoint:NSMakePoint(50, 50)];
    // Moves the window to the front of the screen list, within its level,
    // and makes it the key window; that is, it shows the window.
    [window makeKeyAndOrderFront:nil];
    // Makes the receiver the active app.
    [NSApp activateIgnoringOtherApps:YES];

    MyOpenGLView *testingView = [[MyOpenGLView alloc] initWithFrame:frameSize
    												  pixelFormat:nil];
    [window setContentView:testingView];

    [NSApp run];
    return 0;
}










