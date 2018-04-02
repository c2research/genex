#define BOOST_TEST_MODULE "Test PAAWrapper class"

#include <boost/test/unit_test.hpp>

#define private public
#include "PAAWrapper.hpp"
#include "TimeSeries.hpp"

#define TOLERANCE 1e-7

using namespace genex;

std::string test_10_20_space = "datasets/test/test_10_20_space.txt";

BOOST_AUTO_TEST_CASE( create_paa_wrapper ) {
    TimeSeriesSet tsSet;
    tsSet.loadData(test_10_20_space, -1, 0, " ");
    PAAWrapper paa(tsSet);

    BOOST_CHECK_EQUAL( paa.paaMat.size(), 10);
    for (auto r : paa.paaMat) {
        BOOST_CHECK_EQUAL( r.size(), 1 );
        BOOST_CHECK_EQUAL( r[0].getLength(), 20 );
    }
}

void boostCheckTimeSeries(const TimeSeries& ts, const vector<data_t> actual)
{
    BOOST_REQUIRE_EQUAL( ts.getLength(), actual.size() );
    for (int i = 0; i < ts.getLength(); i++) {
        BOOST_TEST( ts[i] == actual[i] );
    }
}

std::vector<std::vector<data_t> > paa2TruthOffset0 
{{3.858398438,3.333007813,3.041015625,3.893554688,1.97076416,1.229980469,0.993652344,3.560546875,1.7421875,2.48828125},
{2.177490235,1.456176758,3.624023438,1.541503907,3.576171875,1.879394532,2.419921875,3.041015625,2.0625,0.268798828},
{1.808105469,2.154785156,2.488525391,2.076171875,1.401123047,3.278808594,3.31640625,1.505371094,1.139404297,3.365234375},
{2.881591797,2.471191407,1.003967285,2.904785156,2.541992188,1.568359375,2.649414063,1.860839844,2.822265625,1.872558594},
{3.655273438,3.254394531,1.357910156,2.294189453,0.292266846,4.390625,2.531738282,1.577514649,1.589355469,2.314331055},
{3.567382813,1.457519532,4.310546875,0.706726074,3.041992188,3.568359375,2.125,2.519042969,1.236450196,4.118164063},
{2.398803711,2.28125,1.825195313,2.727539063,2.361328125,4.69921875,2.801757813,2.829101563,4.122070313,2.673828125},
{2.999023438,2.840332032,2.395019531,3,2.392578125,1.7578125,1.814453125,1.214111328,2.471679688,2.444580078},
{1.469482422,0.992050171,1.439819336,1.864501953,3.869140625,4.31640625,2.297363281,2.672363281,2.618164063,1.104980469},
{1.930664063,2.157226563,2.861816407,2.719726563,1.868164063,3.022460938,2.457519531,3.521484375,3.09765625,0.270942688}};

std::vector<std::vector<data_t> > paa2TruthOffset1
{{4.435546875,2.954101563,3.028320313,2.252990723,2.772460938,0.698730469,1.862792969,3.325683594,1.997558594,2.537109375},
{3.16015625,2.739379883,1.9921875,2.062011719,2.786621094,2.700195313,2.706054688,2.127929688,1.371704102,0.352783203},
{1.288574219,4.0234375,0.939697266,1.852294922,2.001464844,3.916015625,2.259277344,1.736816406,2.365478516,2.765625},
{1.99194336,1.820800782,2.208068848,1.894042969,2.580078125,1.739257813,1.564941406,2.68359375,3.015625,1.200195312},
{2.431152344,3.090332031,1.011962891,1.851959229,2.58581543,2.901855469,3.01953125,1.679077149,0.305053711,4.31640625},
{3.411132813,2.220214844,2.827148438,1.146179199,3.44140625,3.71875,0.782714844,2.503051758,3.487304688,3.298828125},
{3.822265625,1.125976563,3.60546875,1.772460938,3.423828125,3.926757813,3.190429688,3.271484375,3.37109375,2.068359375},
{2.638183594,2.827636719,3.015625,2.649414063,1.819335938,2.026855469,1.060302734,2.416015625,3.12109375,0.891113281},
{0.989608765,1.201049805,1.468994141,3.305664063,4.40625,3.662109375,1.096679687,4.112304688,1.186035156,1.435546875},
{2.243164063,2.187988282,3.094726563,2.122070313,1.986328125,4.453125,1.643066406,4.294921875,1.3359375,0.002822876}};

BOOST_AUTO_TEST_CASE( generate_paa_matrix_2, *boost::unit_test::tolerance(TOLERANCE) ) {
    TimeSeriesSet tsSet;
    tsSet.loadData(test_10_20_space, -1, 0, " ");
    PAAWrapper paa(tsSet);

    paa.generatePAAMatrix(2);

    BOOST_CHECK_EQUAL( paa.paaMat.size(), 10);
    for (int i = 0; i < paa.paaMat.size(); i++) {
        BOOST_CHECK_EQUAL( paa.paaMat[i].size(), 2 );

        TimeSeries& ts0 = paa.paaMat[i][0];
        boostCheckTimeSeries( ts0, paa2TruthOffset0[i] );

        TimeSeries& ts1 = paa.paaMat[i][1];
        boostCheckTimeSeries( ts1, paa2TruthOffset1[i] );
    }
}

std::vector<std::vector<data_t> > paa3TruthOffset0 
{{3.966796875,2.854817708,2.635457357,2.094075521,1.461914063,2.735677083,2.48828125},
{2.256347656,2.58211263,1.946940104,2.717773438,2.744140625,2.271484375,0.268798828},
{1.37109375,2.92985026,1.613769531,2.890299479,2.560872396,1.413248698,3.365234375},
{2.98030599,1.257527669,2.691080729,1.985677083,1.937174479,2.951171875,1.872558594},
{3.102539062,2.409179687,1.560323079,3.091064453,2.580403646,1.21866862,2.314331055},
{3.25,2.973632813,1.155395508,3.72265625,1.572591146,2.34773763,4.118164063},
{2.665608724,1.671223958,2.664713542,3.860677083,3.166666667,3.335286458,2.673828125},
{2.631835938,2.857747396,2.804036458,1.962890625,1.308105469,2.358723958,2.444580078},
{0.991607666,1.60929362,2.374511719,4.325520833,1.784505208,3.274088542,1.104980469},
{1.858723958,2.774414063,2.162109375,2.911458333,2.476888021,3.57421875,0.270942688}};

std::vector<std::vector<data_t> > paa3TruthOffset1
{{3.784505208,3.160807292,2.776082357,1.040039063,2.816080729,1.974609375,2.537109375},
{2.272867839,2.98828125,2.839518229,2.193033854,2.700520833,1.436604818,0.352783203},
{2.129882812,2.037923177,1.939290365,3.240559896,2.159830729,2.081217448,2.765625},
{1.916178386,2.09769694,2.202799479,1.939453125,2.112955729,2.729817708,1.200195312},
{3.124674479,1.230957031,1.398620605,3.494466146,2.172119141,1.163655599,4.31640625},
{2.374023438,3.264973958,2.107869466,3.4296875,2.045247396,2.470133464,3.298828125},
{3.002604167,2.699869792,1.909505208,4.172526042,2.714192708,3.841145833,2.068359375},
{3.019856771,2.634440104,2.557291667,1.773111979,1.417805989,2.98046875,0.891113281},
{1.309153239,1.130615234,3.651692708,3.930989583,2.259765625,2.003580729,1.435546875},
{2.361979167,2.655273438,2.311197917,3.396484375,2.604492187,2.244791667,0.002822876}};

std::vector<std::vector<data_t> > paa3TruthOffset2
{{3.363932292,3.481119792,1.888061523,0.908203125,3.016601563,2.177408854},
{2.630940755,1.783528646,2.777018229,2.473307292,2.549479167,1.032063802},
{2.847981771,1.631673177,1.563964844,3.766927083,1.5078125,2.498860677},
{2.273111979,1.980183919,2.474609375,2.031901042,1.959960937,2.410481771},
{2.725911458,1.878417969,1.754740397,3.055013021,2.011962891,1.642171224},
{2.351888021,1.964640299,2.978515625,2.845052083,1.824625651,3.424479167},
{1.817057292,2.738932292,3.12890625,3.445963542,3.479817708,2.936848958},
{2.517578125,2.97265625,2.016927083,1.959635417,1.709147135,2.377766927},
{0.812652588,2.051595052,4.069010417,2.919596354,2.994466146,1.269205729},
{2.030273438,3.12890625,1.673177083,3.225585937,3.701822917,0.891565959}};

BOOST_AUTO_TEST_CASE( generate_paa_matrix_3, *boost::unit_test::tolerance(TOLERANCE) ) {
    TimeSeriesSet tsSet;
    tsSet.loadData(test_10_20_space, -1, 0, " ");
    PAAWrapper paa(tsSet);

    paa.generatePAAMatrix(3);

    BOOST_CHECK_EQUAL( paa.paaMat.size(), 10);
    for (int i = 0; i < paa.paaMat.size(); i++) {
        BOOST_CHECK_EQUAL( paa.paaMat[i].size(), 3 );

        TimeSeries& ts0 = paa.paaMat[i][0];
        boostCheckTimeSeries( ts0, paa3TruthOffset0[i] );
        
        TimeSeries& ts1 = paa.paaMat[i][1];
        boostCheckTimeSeries( ts1, paa3TruthOffset1[i] );

        TimeSeries& ts2 = paa.paaMat[i][2];
        boostCheckTimeSeries( ts2, paa3TruthOffset2[i] );
    }
}

BOOST_AUTO_TEST_CASE( get_paa, *boost::unit_test::tolerance(TOLERANCE) ) {
    TimeSeriesSet tsSet;
    tsSet.loadData(test_10_20_space, -1, 0, " ");
    PAAWrapper paa(tsSet);

    paa.generatePAAMatrix(3);
    
    vector<data_t> actual1 {3.25, 2.973632813, 1.155395508, 4.03125};
    TimeSeries paa1 = paa.getPAA(5, 0, 10);
    boostCheckTimeSeries( paa1, actual1 );

    vector<data_t> actual2 {1.308105469, 2.358723958};
    TimeSeries paa2 = paa.getPAA(7, 12, 18);
    boostCheckTimeSeries( paa2, actual2 );

    vector<data_t> actual3 {3.624023438};
    TimeSeries paa3 = paa.getPAA(1, 4, 6);
    boostCheckTimeSeries( paa3, actual3 );

    paa.generatePAAMatrix(4);
    vector<data_t> actual4 {1.737579346, 2.723388672, 2.108886719, 1.959960937};
    TimeSeries paa4 = paa.getPAA(3, 2, 17);
    boostCheckTimeSeries( paa4, actual4 );

}
