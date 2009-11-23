//
//  istkeyAppDelegate.m
//  istkey
//
//  Created by xant on 11/20/09.
//  Copyright xant.net 2009. All rights reserved.
//

#import "istkeyAppDelegate.h"
#import "istkeyViewController.h"

@implementation istkeyAppDelegate

@synthesize window;
@synthesize viewController;


- (void)applicationDidFinishLaunching:(UIApplication *)application {    
    
    // Override point for customization after app launch    
    [window addSubview:viewController.view];
    [window makeKeyAndVisible];
}


- (void)dealloc {
    [viewController release];
    [window release];
    [super dealloc];
}


@end
