#import "ViewController.h"
#import <OpenGLES/ES2/glext.h>
#import "../faaab.Shared/SimpleRenderer.h"
#import <memory>

UITextField* activeField;
BOOL e;

@interface ViewController () {}


@property (weak, nonatomic) IBOutlet UIScrollView *scrollView;

@property (weak, nonatomic) IBOutlet UITextView *ffff;

@property (weak, nonatomic) IBOutlet UITextView *gggg;
@property (weak, nonatomic) IBOutlet UIButton *C;
@property (weak, nonatomic) IBOutlet UIView *Vi;




@end

@implementation ViewController
{
  std::unique_ptr<SimpleRenderer> mCubeRenderer;
}

- (void)viewDidLoad
{
    [_scrollView addSubview:_Vi];
    self.scrollView.contentSize = self.Vi.frame.size;
    //_scrollView.contentSize = _scrollView.frame.size;
    //[_scrollView addSubview:_Vi];
    //self.navigationController.navigationBar.translucent = NO;
    //self.navigationController.navigationBarHidden = YES;
      [super viewDidLoad];
      _gggg.editable = NO;
    _gggg.text = @"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
    [self registerForKeyboardNotifications];
    dispatch_async(dispatch_queue_create("getDbSize", NULL), ^{
    
          while(1){
                //printf("%s ", mCubeRenderer->rts());
                //printf("%s\n", ha);
                //usleep(10000);
              if(self->mCubeRenderer->yn() == true){
                      printf(" kk \n");

                  self->mCubeRenderer->ync();
                      dispatch_async(dispatch_get_main_queue(), ^{
                          NSString* ha = [NSString stringWithUTF8String: self->mCubeRenderer->rts()];
                          
                          NSString *sa = [self->_gggg text];
                              NSString *ss = [NSString stringWithFormat:@"%@\n%@\n", sa, ha];
                          self->_gggg.text = ss;
                            //printf("%s", ss.UTF8String);
                          [self->_gggg scrollRangeToVisible:NSMakeRange(self->_gggg.text.length-1, 1)];
                      });
                }
          }
    });
    e = true;
      
}

- (void)dealloc
{
}

- (void)didReceiveMemoryWarning
{
  [super didReceiveMemoryWarning];
  // Dispose of any resources that can be recreated.
}

- (BOOL)prefersStatusBarHidden {
  return NO;
}

// Call this method somewhere in your view controller setup code.
- (void)registerForKeyboardNotifications
{
    [[NSNotificationCenter defaultCenter] addObserver:self
            selector:@selector(keyboardWasShown:)
            name:UIKeyboardDidShowNotification object:nil];
 
   [[NSNotificationCenter defaultCenter] addObserver:self
             selector:@selector(keyboardWillBeHidden:)
             name:UIKeyboardWillHideNotification object:nil];
 
}
 
// Called when the UIKeyboardDidShowNotification is sent.
- (void)keyboardWasShown:(NSNotification*)aNotification
{
    printf("111");
    NSDictionary* info = [aNotification userInfo];
    CGSize kbSize = [[info objectForKey:UIKeyboardFrameEndUserInfoKey] CGRectValue].size;
 
    UIEdgeInsets contentInsets = UIEdgeInsetsMake(0.0, 0.0, kbSize.height, 0.0);
    _scrollView.contentInset = contentInsets;
    _scrollView.scrollIndicatorInsets = contentInsets;
 
    // If active text field is hidden by keyboard, scroll it so it's visible
    // Your app might not need or want this behavior.
    CGRect he = CGRectMake(7,630,290,23);

        [self.scrollView scrollRectToVisible:he animated:YES];
}
 
// Called when the UIKeyboardWillHideNotification is sent
- (void)keyboardWillBeHidden:(NSNotification*)aNotification
{
    printf("222");
    UIEdgeInsets contentInsets = UIEdgeInsetsZero;
    _scrollView.contentInset = contentInsets;
    _scrollView.scrollIndicatorInsets = contentInsets;
    CGRect he = CGRectMake(0,0,1,1);
    [self.scrollView scrollRectToVisible:he animated:YES];
}

- (IBAction)ennt:(id)sender {
  NSString *s1 = [_ffff text];
  const char* ss1 = s1.UTF8String;
  NSString *aaa = [NSString stringWithFormat:@"%@\n>me: %@\n", _gggg.text, _ffff.text];
  _gggg.text = aaa;
  [_gggg scrollRangeToVisible:NSMakeRange(_gggg.text.length-1, 1)];
  mCubeRenderer->sts(ss1);
  _ffff.text = @"";
}

- (IBAction)cnct:(id)sender {
    NSString *s1 = [_ffff text];
    if(e == true){
        e = false;
        _C.enabled = false;
        _C.backgroundColor = [UIColor grayColor];
        dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
            const char* ss1 = s1.UTF8String;
            self->mCubeRenderer->SSS(ss1,"71.202.170.28");
            dispatch_async(dispatch_get_main_queue(), ^{
                self->_C.enabled = true;
                e = true;
                if (@available(iOS 15.0, *)) {
                    self->_C.backgroundColor = [UIColor systemMintColor];
                } else {
                    self->_C.backgroundColor = [UIColor systemBlueColor];// Fallback on earlier versions
                }
            });
        });
        _ffff.text = @"";
    }
    else{
        printf("he");
    }
}

@end
