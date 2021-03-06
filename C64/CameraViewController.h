//
//  ColorTrackingViewController.h
//  ColorTracking
//
//
//  The source code for this application is available under a BSD license.  See License.txt for details.
//
//  Created by Brad Larson on 10/7/2010.
//

#import <UIKit/UIKit.h>
#import "Camera.h"
#import "CameraGLView.h"
#import <AudioToolbox/AudioToolbox.h>

typedef enum { PASSTHROUGH_VIDEO, SIMPLE_THRESHOLDING, POSITION_THRESHOLDING, OBJECT_TRACKING} ColorTrackingDisplayMode;

@class GLKTextureInfo;
@interface CameraViewController : UIViewController <CameraDelegate, UIActionSheetDelegate> {
    BOOL m_setup;
    int numTextureSteps;
    GLuint* m_hTexture;
    GLuint* m_hFBO;
    
    GLKTextureInfo* ditherTexture;
    GLKTextureInfo* paletteTexture;
    
	Camera *camera;
	UIScreen *screenForDisplay;
	CameraGLView *glView;
    UISlider* sliderControl;
    UILabel* debugLabel;
    UIImageView* overlay;
    NSTimeInterval lastTime;
    
    BOOL toolbarShown;
    NSTimer* hideTimer;
    NSInvocation* hideInvocation;
    UIToolbar *lowerToolbar;
	ColorTrackingDisplayMode displayMode;

	double weekNum;
	BOOL weekNumChanged;
    
    SystemSoundID shutterSoundID;
			
	BOOL programLoaded;
    GLuint c64FilterProgram, colorFilterFrame, ditherMap, paletteMap, textureScale;
    CGFloat textureScaleValue;
    
	GLuint videoFrameTexture;
	size_t bufferWidth, bufferHeight;
	
    // filter properties are all derived from weeks, and all are updated with a call to setWeeks:
    float weeks;
    int smoothingPasses;
    double smoothing;
    
    BOOL grabNextPicture, pauseFilter;
    UIImage* grabbedImage;
}

@property(readonly) CameraGLView *glView;

// Initialization and teardown
-(id)initWithScreen:(UIScreen *)newScreenForDisplay;

// OpenGL ES 2.0 setup methods
- (BOOL)loadFilterShader:(NSString *)vertexShaderName fragmentShader:(NSString *)fragmentShaderName forProgram:(GLuint *)programPointer;
- (BOOL)compileShader:(GLuint *)shader type:(GLenum)type file:(NSString *)file;
- (BOOL)linkProgram:(GLuint)prog;
- (BOOL)validateProgram:(GLuint)prog;

// Display mode switching
- (void)handleSwitchOfDisplayMode:(id)sender;

// weeks should be >= 1.0
-(void)setWeeks:(float)weeks;

-(void)startConfig;
-(void)showToolbar:(BOOL)animated;
-(void)neverHideToolbar;

@end

