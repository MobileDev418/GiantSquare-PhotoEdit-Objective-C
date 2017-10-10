//
//  MPAdBrowserController.h
//  MoPub
//
//  Created by Nafis Jamal on 1/19/11.
//  Copyright 2011 MoPub, Inc. All rights reserved.
//

#import <UIKit/UIKit.h>

#ifndef CF_RETURNS_RETAINED
#if __has_feature(attribute_cf_returns_retained)
#define CF_RETURNS_RETAINED __attribute__((cf_returns_retained))
#else
#define CF_RETURNS_RETAINED
#endif
#endif

@protocol MPAdBrowserControllerDelegate;

@interface MPAdBrowserController : UIViewController <UIWebViewDelegate, UIActionSheetDelegate>
{
	id<MPAdBrowserControllerDelegate> _delegate;
	UIWebView *_webView;
	UIBarButtonItem *_backButton;
	UIBarButtonItem *_forwardButton;
	UIBarButtonItem *_refreshButton;
	UIBarButtonItem *_safariButton;
	UIBarButtonItem *_doneButton;
	UIActivityIndicatorView *_spinner;
	UIBarButtonItem *_spinnerItem;
	UIActionSheet *_actionSheet;
	BOOL _actionSheetIsShowing;
	NSURL *_URL;
    
    // The number of calls to -webViewDidStartLoad: that have not yet been matched by a call to
    // -webViewDidFinishLoad:. This gives us a rudimentary way to determine when the current page
    // has loaded completely.
    NSInteger _webViewLoadCount;
    
    // Whether this browser's current page load has caused it to leave the application. This value
    // is reset to NO upon each call to -startLoading.
    BOOL _hasLeftApplicationForCurrentURL;
    
    // Whether the browser is currently animating onto the screen (i.e. it is between calls to
    // -viewWillAppear: and -viewDidAppear).
    BOOL _isPerformingPresentationAnimation;
}

@property (nonatomic, retain) IBOutlet UIWebView *webView;
@property (nonatomic, retain) IBOutlet UIBarButtonItem *backButton;
@property (nonatomic, retain) IBOutlet UIBarButtonItem *forwardButton;
@property (nonatomic, retain) IBOutlet UIBarButtonItem *refreshButton;
@property (nonatomic, retain) IBOutlet UIBarButtonItem *safariButton;
@property (nonatomic, retain) IBOutlet UIBarButtonItem *doneButton;
@property (nonatomic, retain) IBOutlet UIBarButtonItem *spinnerItem;

@property (nonatomic, assign) id<MPAdBrowserControllerDelegate> delegate;
@property (nonatomic, copy) NSURL *URL;

- (id)initWithURL:(NSURL *)URL delegate:(id<MPAdBrowserControllerDelegate>)delegate;
- (void)startLoading;
- (void)stopLoading;

// Navigation methods.
- (IBAction)back;
- (IBAction)forward;
- (IBAction)refresh;
- (IBAction)safari;
- (IBAction)done;

// Drawing methods.
- (CGContextRef)createContext CF_RETURNS_RETAINED;
- (UIImage *)backArrowImage;
- (UIImage *)forwardArrowImage;

@end

////////////////////////////////////////////////////////////////////////////////////////////////////

@protocol MPAdBrowserControllerDelegate <NSObject>
@required
- (void)dismissBrowserController:(MPAdBrowserController *)browserController;
- (void)dismissBrowserController:(MPAdBrowserController *)browserController animated:(BOOL)animated;

@optional
- (void)browserControllerDidFinishLoad:(MPAdBrowserController *)browserController;
- (void)browserControllerWillLeaveApplication:(MPAdBrowserController *)browserController;
@end