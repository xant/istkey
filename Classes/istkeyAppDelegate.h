//
//  istkeyAppDelegate.h
//  istkey
//
//  Created by xant on 11/20/09.
//  Copyright xant.net 2009. All rights reserved.
//

#import <UIKit/UIKit.h>

@class istkeyViewController;

@interface istkeyAppDelegate : NSObject <UIApplicationDelegate> {
    UIWindow *window;
    istkeyViewController *viewController;
}

@property (nonatomic, retain) IBOutlet UIWindow *window;
@property (nonatomic, retain) IBOutlet istkeyViewController *viewController;

@end

