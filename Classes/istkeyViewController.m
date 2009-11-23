//
//  istkeyViewController.m
//  istkey
//
//  Created by xant on 11/20/09.
//  Copyright xant.net 2009. All rights reserved.
//
//3EE8E0
//C5BD71

#import "istkeyViewController.h"

int compute_key(char *strId, int year, char *output, int len);

@implementation istkeyViewController

/*
// The designated initializer. Override to perform setup that is required before the view is loaded.
- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil {
    if (self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil]) {
        // Custom initialization
    }
    return self;
}
*/

/*
// Implement loadView to create a view hierarchy programmatically, without using a nib.
- (void)loadView {
}
*/


/*
// Implement viewDidLoad to do additional setup after loading the view, typically from a nib.
- (void)viewDidLoad {
    [super viewDidLoad];
}
*/

/*
// Override to allow orientations other than the default portrait orientation.
- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation {
    // Return YES for supported orientations
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
}
*/

- (void)didReceiveMemoryWarning {
	// Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
	
	// Release any cached data, images, etc that aren't in use.
}

- (void)viewDidUnload {
	// Release any retained subviews of the main view.
	// e.g. self.myOutlet = nil;
}

- (void)dealloc {
    [super dealloc];
}

- (void)getKeys {
    char *input = (char *)[
                    [[[ssid text] 
                     stringByReplacingOccurrencesOfString:@"SpeedTouch" withString:@""]
                     stringByReplacingOccurrencesOfString:@"speedtouch" withString:@""]
                    UTF8String];
    int year = 7; // defaults to 2007
    char *yearStr = (char *)[[productionYear titleForSegmentAtIndex:
                        [productionYear selectedSegmentIndex]
                     ] UTF8String];

    if (!yearStr
        || sscanf(yearStr, "%u", &year) != 1 
        || year < 2000) 
    {
        // TODO - Error messages
        return;
    }
    year-=2000; // compute_key expects it as offset from year 2000
    int nKeys = compute_key(input, year, output, sizeof(output));
    if (nKeys) {
        [keysPanel setText:[NSString stringWithUTF8String:output]];
        [outLabel setText:[NSString stringWithFormat:@"%d possible keys found:", nKeys]];
    } else {
        [keysPanel setText:@"No possible keys found.\nTry a different production year."];
    }
    [activityIndicator stopAnimating];    
}

- (IBAction)doit:(id)sender {
    [keysPanel setText:@""];
    [outLabel setText:@""];
    [activityIndicator startAnimating];
    [self performSelector:@selector(getKeys) withObject:self afterDelay:0.1];
}

@end
