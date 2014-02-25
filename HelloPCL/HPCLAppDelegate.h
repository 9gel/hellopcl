//
//  HPCLAppDelegate.h
//  HelloPCL
//
//  Created by Nigel Choi on 2/24/14.
//  Copyright (c) 2014 Nigel Choi. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "LoadDataController.h"

@class EAGLView;
@class GLViewController;

@interface HPCLAppDelegate : UIResponder <UIApplicationDelegate,LoadDataDelegate> {
    UIWindow *window;
    EAGLView *glView;
    
    UIAlertView* waitDialog;
    
    dispatch_queue_t myQueue;
    
    
    LoadDataController *_dataLoader;
    UIPopoverController *_loadDataPopover;
}

@property (nonatomic, retain) IBOutlet UIWindow *window;
@property (nonatomic, retain) IBOutlet EAGLView *glView;
@property (nonatomic, retain) IBOutlet GLViewController *viewController;
@property (nonatomic, retain) LoadDataController *dataLoader;
@property (nonatomic, retain) UIPopoverController *loadDataPopover;


@property (nonatomic, retain) IBOutlet UILabel *opacityLabel;
@property (nonatomic, retain) IBOutlet UISlider *opacitySlider;

@property (nonatomic, retain) IBOutlet UILabel *voxelLabel;
@property (nonatomic, retain) IBOutlet UISegmentedControl *voxelButtons;

@property (nonatomic, retain) IBOutlet UILabel *ransacLabel;
@property (nonatomic, retain) IBOutlet UISegmentedControl *ransacButtons;

@property (nonatomic, retain) IBOutlet UIActivityIndicatorView *voxelIndicator;
@property (nonatomic, retain) IBOutlet UIActivityIndicatorView *ransacIndicator;

-(IBAction)reset:(UIButton*)sender;
-(IBAction)information:(UIButton*)sender;
-(IBAction)setLoadDataButtonTapped:(id)sender;

-(IBAction) opacitySliderValueChanged:(UISlider*)sender;
-(IBAction) voxelGridIndexChanged;
-(IBAction) ransacIndexChanged;

- (void)showAlertDialogWithTitle:(NSString *)alertTitle message:(NSString *)alertMessage;

-(void)dismissLoadDataView;

- (BOOL)handleUrl:(NSURL *)url;

@end
