//
//  NSIndexSetBlocksKitTest.h
//  BlocksKit Unit Tests
//

#import <GHUnitIOS/GHUnit.h>
#import "BlocksKit/BlocksKit.h"

@interface NSIndexSetBlocksKitTest : GHTestCase {
    NSIndexSet *_subject;
    NSMutableArray  *_target;
}

- (void)testEach;
- (void)testMatch;
- (void)testNotMatch;
- (void)testSelect;
- (void)testSelectedNone;
- (void)testReject;
- (void)testRejectedNone;

@end
