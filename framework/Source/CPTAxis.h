#import <Foundation/Foundation.h>
#import "CPTLayer.h"
#import "CPTDefinitions.h"
#import "CPTTextStyle.h"

///	@file

@class CPTAxis;
@class CPTAxisSet;
@class CPTAxisTitle;
@class CPTGridLines;
@class CPTLimitBand;
@class CPTLineStyle;
@class CPTPlotSpace;
@class CPTPlotRange;
@class CPTPlotArea;

/**	@brief Enumeration of labeling policies
 **/
typedef enum _CPTAxisLabelingPolicy {
    CPTAxisLabelingPolicyNone,					///< No labels provided; user sets labels and tick locations.
    CPTAxisLabelingPolicyLocationsProvided,		///< User sets tick locations; axis makes labels.
    CPTAxisLabelingPolicyFixedInterval,			///< Fixed interval labeling policy.
	CPTAxisLabelingPolicyAutomatic,				///< Automatic labeling policy.
	CPTAxisLabelingPolicyEqualDivisions			///< Divide the plot range into equal parts.
} CPTAxisLabelingPolicy;

#pragma mark -

/**	@brief Axis labeling delegate.
 **/
@protocol CPTAxisDelegate <NSObject>

/// @name Labels
/// @{

/**	@brief Determines if the axis should relabel itself now.
 *	@param axis The axis.
 *	@return YES if the axis should relabel now.
 **/
-(BOOL)axisShouldRelabel:(CPTAxis *)axis;

/**	@brief The method is called after the axis is relabeled to allow the delegate to perform any
 *	necessary cleanup or further labeling actions.
 *	@param axis The axis.
 **/
-(void)axisDidRelabel:(CPTAxis *)axis;

@optional

/**	@brief This method gives the delegate a chance to create custom labels for each tick.
 *  It can be used with any relabeling policy. Returning NO will cause the axis not
 *  to update the labels. It is then the delegates responsiblity to do this.
 *	@param axis The axis.
 *  @param locations The locations of the major ticks.
 *  @return YES if the axis class should proceed with automatic relabeling.
 **/
-(BOOL)axis:(CPTAxis *)axis shouldUpdateAxisLabelsAtLocations:(NSSet *)locations;

///	@}

@end

#pragma mark -

@interface CPTAxis : CPTLayer {   
	@private
    CPTCoordinate coordinate;
	CPTPlotSpace *plotSpace;
    NSSet *majorTickLocations;
    NSSet *minorTickLocations;
    CGFloat majorTickLength;
    CGFloat minorTickLength;
	CGFloat labelOffset;
	CGFloat minorTickLabelOffset;
    CGFloat labelRotation;
    CGFloat minorTickLabelRotation;
	CPTAlignment labelAlignment;
	CPTAlignment minorTickLabelAlignment;
    CPTLineStyle *axisLineStyle;
    CPTLineStyle *majorTickLineStyle;
    CPTLineStyle *minorTickLineStyle;
    CPTLineStyle *majorGridLineStyle;
    CPTLineStyle *minorGridLineStyle;
    NSDecimal labelingOrigin;			
    NSDecimal majorIntervalLength;	
    NSUInteger minorTicksPerInterval;
    NSUInteger preferredNumberOfMajorTicks;
    CPTAxisLabelingPolicy labelingPolicy;
	CPTTextStyle *labelTextStyle;
	CPTTextStyle *minorTickLabelTextStyle;
	CPTTextStyle *titleTextStyle;
	NSNumberFormatter *labelFormatter;
	NSNumberFormatter *minorTickLabelFormatter;
	BOOL labelFormatterChanged;
	NSSet *axisLabels;
	NSSet *minorTickAxisLabels;
	CPTAxisTitle *axisTitle;
	NSString *title;
	CGFloat titleOffset;
	CGFloat titleRotation;
	NSDecimal titleLocation;	
    CPTSign tickDirection;
    BOOL needsRelabel;
	NSArray *labelExclusionRanges;
    CPTPlotRange *visibleRange;
    CPTPlotRange *gridLinesRange;
	NSArray *alternatingBandFills;
	NSMutableArray *mutableBackgroundLimitBands;
	BOOL separateLayers;
	__weak CPTPlotArea *plotArea;
	__weak CPTGridLines *minorGridLines;
	__weak CPTGridLines *majorGridLines;
}

/// @name Axis
/// @{
@property (nonatomic, readwrite, copy) CPTLineStyle *axisLineStyle;
@property (nonatomic, readwrite, assign) CPTCoordinate coordinate;
@property (nonatomic, readwrite, assign) NSDecimal labelingOrigin;
@property (nonatomic, readwrite, assign) CPTSign tickDirection;
@property (nonatomic, readwrite, copy) CPTPlotRange *visibleRange;
///	@}

/// @name Title
/// @{
@property (nonatomic, readwrite, copy) CPTTextStyle *titleTextStyle;
@property (nonatomic, readwrite, retain) CPTAxisTitle *axisTitle;
@property (nonatomic, readwrite, assign) CGFloat titleOffset;
@property (nonatomic, readwrite, copy) NSString *title;
@property (nonatomic, readwrite, assign) CGFloat titleRotation;
@property (nonatomic, readwrite, assign) NSDecimal titleLocation;
@property (nonatomic, readonly, assign) NSDecimal defaultTitleLocation;
///	@}

/// @name Labels
/// @{
@property (nonatomic, readwrite, assign) CPTAxisLabelingPolicy labelingPolicy;
@property (nonatomic, readwrite, assign) CGFloat labelOffset;
@property (nonatomic, readwrite, assign) CGFloat minorTickLabelOffset;
@property (nonatomic, readwrite, assign) CGFloat labelRotation;
@property (nonatomic, readwrite, assign) CGFloat minorTickLabelRotation;
@property (nonatomic, readwrite, assign) CPTAlignment labelAlignment;
@property (nonatomic, readwrite, assign) CPTAlignment minorTickLabelAlignment;
@property (nonatomic, readwrite, copy) CPTTextStyle *labelTextStyle;
@property (nonatomic, readwrite, copy) CPTTextStyle *minorTickLabelTextStyle;
@property (nonatomic, readwrite, retain) NSNumberFormatter *labelFormatter;
@property (nonatomic, readwrite, retain) NSNumberFormatter *minorTickLabelFormatter;
@property (nonatomic, readwrite, retain) NSSet *axisLabels;
@property (nonatomic, readwrite, retain) NSSet *minorTickAxisLabels;
@property (nonatomic, readonly, assign) BOOL needsRelabel;
@property (nonatomic, readwrite, retain) NSArray *labelExclusionRanges;

// HACK: properties for messing with the axis labels. 
@property (nonatomic, readwrite, assign) CGFloat labelValueOffset; 
@property (nonatomic, readwrite, assign) CGFloat labelValueFactor;

///	@}

/// @name Major Ticks
/// @{
@property (nonatomic, readwrite, assign) NSDecimal majorIntervalLength;
@property (nonatomic, readwrite, assign) CGFloat majorTickLength;
@property (nonatomic, readwrite, copy) CPTLineStyle *majorTickLineStyle;
@property (nonatomic, readwrite, retain) NSSet *majorTickLocations;
@property (nonatomic, readwrite, assign) NSUInteger preferredNumberOfMajorTicks;
///	@}

/// @name Minor Ticks
/// @{
@property (nonatomic, readwrite, assign) NSUInteger minorTicksPerInterval;
@property (nonatomic, readwrite, assign) CGFloat minorTickLength;
@property (nonatomic, readwrite, copy) CPTLineStyle *minorTickLineStyle;
@property (nonatomic, readwrite, retain) NSSet *minorTickLocations;
///	@}

/// @name Grid Lines
/// @{
@property (nonatomic, readwrite, copy) CPTLineStyle *majorGridLineStyle;
@property (nonatomic, readwrite, copy) CPTLineStyle *minorGridLineStyle;
@property (nonatomic, readwrite, copy) CPTPlotRange *gridLinesRange;
///	@}

/// @name Background Bands
/// @{
@property (nonatomic, readwrite, copy) NSArray *alternatingBandFills;
@property (nonatomic, readonly, retain) NSArray *backgroundLimitBands;
///	@}

/// @name Plot Space
/// @{
@property (nonatomic, readwrite, retain) CPTPlotSpace *plotSpace;
///	@}

/// @name Layers
/// @{
@property (nonatomic, readwrite, assign) BOOL separateLayers;
@property (nonatomic, readwrite, assign) __weak CPTPlotArea *plotArea;
@property (nonatomic, readonly, assign) __weak CPTGridLines *minorGridLines;
@property (nonatomic, readonly, assign) __weak CPTGridLines *majorGridLines;
@property (nonatomic, readonly, retain) CPTAxisSet *axisSet;
///	@}

/// @name Labels
/// @{
-(void)relabel;
-(void)setNeedsRelabel;
///	@}

/// @name Ticks
/// @{
-(NSSet *)filteredMajorTickLocations:(NSSet *)allLocations;
-(NSSet *)filteredMinorTickLocations:(NSSet *)allLocations;
///	@}

/// @name Background Bands
/// @{
-(void)addBackgroundLimitBand:(CPTLimitBand *)limitBand;
-(void)removeBackgroundLimitBand:(CPTLimitBand *)limitBand;
///	@}

@end

#pragma mark -

/**	@category CPTAxis(AbstractMethods)
 *	@brief CPTAxis abstract methods—must be overridden by subclasses
 **/
@interface CPTAxis(AbstractMethods)

/// @name Coordinate Space Conversions
/// @{
-(CGPoint)viewPointForCoordinateDecimalNumber:(NSDecimal)coordinateDecimalNumber;
///	@}

/// @name Grid Lines
/// @{
-(void)drawGridLinesInContext:(CGContextRef)context isMajor:(BOOL)major;
///	@}

/// @name Background Bands
/// @{
-(void)drawBackgroundBandsInContext:(CGContextRef)context;
-(void)drawBackgroundLimitsInContext:(CGContextRef)context;
///	@}

@end

