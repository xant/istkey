//
//  istkeyViewController.h
//  istkey
//
//  Created by xant on 11/20/09.
//  Copyright xant.net 2009. All rights reserved.
//

#import <UIKit/UIKit.h>
#include "common.h"

@interface istkeyViewController : UIViewController {
    char output[MAX_KEYS*(OUTPUT_KEY_SIZE)+1];
    IBOutlet UITextField *ssid;
    IBOutlet UISegmentedControl *productionYear;
    IBOutlet UITextView *keysPanel;
    IBOutlet UILabel *outLabel;
    IBOutlet UIActivityIndicatorView *activityIndicator;
}
- (IBAction)doit:(id)sender;
@end

