//
//  NSURLConnection+BlocksKit.h
//  %PROJECT
//

#import "BKGlobals.h"

typedef void (^BKProgressBlock) (CGFloat progress);
typedef void (^BKConnectionFinishBlock) (NSURLResponse *response, NSData *data);

/** NSURLConnection with both delegate and block callback support
 
 This category allows you to assign blocks on NSURLConnection
 delegate callbacks, while still allowing the normal delegation
 pattern!
 
 It also adds useful block handlers for tracking upload and
 download progress.
 
 Here is a small example:
     - (void)downloadImage:(id)sender {
         self.downloadButton.enabled = NO;
         self.progressView.progress = 0.0f;
         NSURL *imageURL = [NSURL URLWithString:@"http://icanhascheezburger.files.wordpress.com/2011/06/funny-pictures-nyan-cat-wannabe1.jpg"];
         NSURLRequest *request = [NSURLRequest requestWithURL:imageURL];
         NSURLConnection *connection = [NSURLConnection connectionWithRequest:request];
         connection.delegate = self;
         connection.failureBlock = ^(NSError *error){
             [[UIAlertView alertWithTitle:@"Download error" message:[error localizedDescription]] show];
             
             self.downloadButton.enabled = YES;
             self.progressView.progress = 0.0f;
         };
         connection.successBlock = ^(NSURLResponse *response, NSData *responseData){
             self.imageView.image = [UIImage imageWithData:responseData];
             self.downloadButton.enabled = YES;
         };
         connection.downloadBlock = ^(CGFloat progress){
             self.progressView.progress = progress;
         };
         
         [connection start];
     }
     
     //these methods will be called too!
     - (void)connection:(NSURLConnection *)connection didSendBodyData:(NSInteger)bytesWritten totalBytesWritten:(NSInteger)totalBytesWritten totalBytesExpectedToWrite:(NSInteger)totalBytesExpectedToWrite {
         NSLog(@"%s",__PRETTY_FUNCTION__);
     }
     
     - (void)connection:(NSURLConnection *)connection didReceiveResponse:(NSURLResponse *)response {
         NSLog(@"%s",__PRETTY_FUNCTION__);
     }

 Created by Igor Evsukov as [IEURLConnection](https://github.com/evsukov89/IEURLConnection) and contributed to BlocksKit.
*/

@interface NSURLConnection (BlocksKit)

/** A mutable delegate that implements the NSURLConnectionDelegate protocol.
 
 This property allows for both use of block callbacks and delegate methods
 in an instance of NSURLConnection.  It only works on block-backed
 NSURLConnection instances.
 */
@property (nonatomic, assign) id delegate;

/** The block fired once the connection recieves a response from the server.
 Deprecated in favor of responseBlock. */
@property (copy) BKResponseBlock didReceiveResponseHandler DEPRECATED_ATTRIBUTE;

/** The block fired once the connection recieves a response from the server.

 This block corresponds to the connection:didReceiveResponse: method
 of NSURLConnectionDelegate. */
@property (nonatomic, copy) BKResponseBlock responseBlock;

/** The block fired upon the failure of the connection.
 Deprecated in favor of failureBlock. */
@property (copy) BKErrorBlock didFailWithErrorHandler DEPRECATED_ATTRIBUTE;

/** The block fired upon the failure of the connection.

 This block corresponds to the connection:didFailWithError:
 method of NSURLConnectionDelegate. */
@property (nonatomic, copy) BKErrorBlock failureBlock;

/** The block fired upon the successful completion of the connection.
 Deprecated in favor of successBlock. */
@property (copy) BKConnectionFinishBlock didFinishLoadingHandler DEPRECATED_ATTRIBUTE;

/** The block that  upon the successful completion of the connection.

 This block corresponds to the connectionDidFinishLoading:
 method of NSURLConnectionDelegate.

 @warning If the delegate implements connection:didRecieveData:, then this
 block will *not* include the data recieved by the connection and appending
 the recieved data to an instance NSMutableData is left up to the user due
 to the behavior of frameworks that use NSURLConnection.
 */
@property (nonatomic, copy) BKConnectionFinishBlock successBlock;

/** The block fired every time new data is sent to the server,
 representing the current percentage of completion. Deprecated
 in favor of uploadBlock. */
@property (copy) BKProgressBlock uploadProgressHandler DEPRECATED_ATTRIBUTE;

/** The block fired every time new data is sent to the server,
 representing the current percentage of completion.

 This block corresponds to the
 connection:didSendBodyData:totalBytesWritten:totalBytesExpectedToWrite:
 method of NSURLConnectionDelegate.
 */
@property (nonatomic, copy) BKProgressBlock uploadBlock;

/** The block fired every time new data is recieved from the server,
 representing the current percentage of completion. Deprecated
 in favor of downloadBlock. */
@property (copy) BKProgressBlock downloadProgressHandler DEPRECATED_ATTRIBUTE;

/** The block fired every time new data is recieved from the server,
 representing the current percentage of completion.

 This block corresponds to the connection:didRecieveData:
 method of NSURLConnectionDelegate.
 */
@property (nonatomic, copy) BKProgressBlock downloadBlock;

/** Creates and returns an initialized block-backed URL connection that does not begin to load the data for the URL request.
 
 @param request The URL request to load.
 @return An autoreleased NSURLConnection for the specified URL request.
 */
+ (NSURLConnection *)connectionWithRequest:(NSURLRequest *)request;

/** Creates, starts, and returns an asynchronous, block-backed URL connection

 @return New and running NSURLConnection with the specified properties.
 @param request The URL request to load.
 @param success A code block that acts on instances of NSURLResponse and NSData in the event of a successful connection.
 @param failure A code block that acts on instances of NSURLResponse and NSError in the event of a failed connection.
 */
+ (NSURLConnection *)startConnectionWithRequest:(NSURLRequest *)request successHandler:(BKConnectionFinishBlock)success failureHandler:(BKErrorBlock)failure;

/** Returns an initialized block-backed URL connection.
 
 @return Newly initialized NSURLConnection with the specified properties.
 @param request The URL request to load.
 */
- (id)initWithRequest:(NSURLRequest *)request;

/** Returns an initialized URL connection with the specified completion handler.
 
 @return Newly initialized NSURLConnection with the specified properties.
 @param request The URL request to load.
 @param block A code block that acts on instances of NSURLResponse and NSData in the event of a successful connection.
 */
- (id)initWithRequest:(NSURLRequest *)request completionHandler:(BKConnectionFinishBlock)block;

/** Causes the connection to begin loading data, if it has not already, with the specified block to be fired on successful completion.
 
 @param block A code block that acts on instances of NSURLResponse and NSData in the event of a successful connection.
 */
- (void)startWithCompletionBlock:(BKConnectionFinishBlock)block;

@end
