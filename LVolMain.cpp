//
//  LVolMain.cpp
//  MCPricing
//
//  Created by Xiangyu Joshua Li on 27/03/2016.
//  Copyright © 2016 Xiangyu Joshua Li. All rights reserved.
//

#include "BSLocalVolatilityProcess.hpp"
#include "LocalVolatilitySurface.hpp"
#include "FDEuropeanLVEngine.hpp"
#include "FDEuropeanCEVEngine.hpp"
#include "CEV.hpp"
#include "All.h"
#include <vector>
#include <memory>
#include <cmath>
#include <stdio.h>
#include <fstream>
#include <cstdlib>

using std::vector;
using std::shared_ptr;
using std::ifstream;

int main()
{

    RandomGen::SetSeed((unsigned int)time(NULL));
    
    double Price = 2.140;
    double Rate  = 0.021;
    double Rho = 0.0;
    
    // Local Volatility Surface
    
    // Maturities range from 0.1 to 1.0.
    size_t T = 13;
    vector<double> Maturities{0.1000, 0.1699, 0.2000, 0.2466, 0.3000, 0.4000, 0.5000, 0.5151, 0.6000, 0.7000, 0.8000, 0.9000,1.0000};
    
    // Moneynesses range from 0.92 to 1.18.
    size_t K = 14;
    vector<vector<double>> Strikes(T);
    
    for (size_t i = 0; i < T; ++i)
    {
        double Forward = Price * exp( (Rate - Rho)*Maturities[i] );
        Strikes[i].resize(K);
        for (size_t j = 0; j < K; ++j)
        {
            double Moneyness = 0.92 + j*0.02; // Generate moneyness from 0.92 to 1.18.
            Strikes[i][j] = Moneyness * Forward;
        }
    }
    
    // Local Variance Entries $\sigma^2(K,T)$.
//    vector<vector<double>> LVols = {
//        {0.0290222865545293,	0.0404051859785075,	0.0366418641054539,	0.0152260255919644,	0.0381911946929438,	0.0323852525930382,	0.154571840130801,	0.207270779205786,	0,	0.00514003434922185,	0.0119924975265779,	0.0152171800222815,	0.01714214383284},
//        {0.0279593665991061,	0.0457445933229781,	0.0391908491179129,	0.0203469517739457,	0.0455346678032686,	0.0417248933093863,	0.131678367201826,	0.089781565480159,	0.00398441346043517,	0.00588350181765395,	0.011704140477808,	0.0150217896808889,	0.0170285519771712},
//        {0.0794502273557431,	0.0606111152627078,	0.0639796677287783,	0.129646433084513,	0.0523759364370133,	0.0521805414784327,	0.0244958347768086,	0.0150671565023977,	0.0206096599309599,	0.00853731157200505,	0.0128103848315547,	0.01632250657433,	0.0185434348114523},
//        {0.0430623645540436,	0.107762801744656,	0.0859290477569612,	0.149009889583605,	0.0656722402577079,	0.0593364239732193,	0.0167126073814598,	0.0107967157973084,	0.0301860642400778,	0.0114824329179386,	0.0137576828961421,	0.0171396929369323,	0.0194539932157212},
//        {0.0630605877056725,	0.0530056440117456,	0.0914837287099363,	0.0803126957860546,	0.0817201092409785,	0.0671009208141339,	0.090645091292896,	0.0545951118845475,	0.0272403282885114,	0.0144498508493171,	0.0150375834567887,	0.0180807477447734,	0.020409533788013},
//        {0.0577694557750827,	0.0804800614260973,	0.0970068281413234,	0.212605117256037,	0.0889599064049055,	0.0749395398063854,	2.8344254162548,	0,	0.0270377400856269,	0.0176191928578632,	0.0166157533201232,	0.0191331972643472,	0.0213824556976904},
//        {0.058342076848099,	0.0682649423946136,	0.0816378298304681,	0.0855766472412133,	0.0883063529390444,	0.0817811599847483,	0.101833248591394,	0.0845791645007269,	0.0339776874545132,	0.0212323508682441,	0.0184794586615695,	0.0203257759309423,	0.0224001636871342},
//        {0.062541519551035,	0.0583541174888372,	0.0739154692211212,	0.0547644970391556,	0.0894206646161159,	0.0869592185505975,	0.0273203728114017,	0.0213119602970468,	0.0447541098347927,	0.0250177211109526,	0.0206046012923406,	0.0216774983002247,	0.0234862221863065},
//        {0.053353626275739,	0.0674525476761483,	0.0813535784601156,	0.153307489778356,	0.0899716475746844,	0.090985844198917,	0.101807097929085,	0.0811504614456033,	0.0447751812758505,	0.0286648106415544,	0.022957407398975,	0.0231944699490908,	0.0246558582445034},
//        {0.0598674741108094,	0.0719906409912647,	0.0848746453101089,	0.0825541672596123,	0.0928474465629288,	0.094344070454339,	0.150848899556319,	0.153148023262867,	0.0472803644250779,	0.0322022636753189,	0.0255005453027287,	0.0248731192424286,	0.025917939341868},
//        {0.068180049636915,	0.0722537760534037,	0.0851317967415768,	0.0882058402232421,	0.0923274872624035,	0.0966938283242181,	0.0826383573332537,	0.0609965306170279,	0.0534408667086841,	0.0357783673047574,	0.0281976630649599,	0.0267038655234907,	0.0272773395054689},
//        {0.0741602000036701,	0.0712756114479108,	0.0829750019166848,	0.110216637412469,	0.0903140276409428,	0.0981401748412071,	0.0899600329673533,	0.071776159254714,	0.0576517304173742,	0.0395085992101351,	0.0310719781534725,	0.028726766075245,	0.028790125206301},
//        {0.0789912567928764,	0.0681179533869453,	0.0755193781615461,	0.0639909615229427,	0.0867593967795001,	0.0967679500384626,	0.0866722101811009,	0.0699990077013226,	0.0598199437748911,	0.0423405901588988,	0.0333269141685755,	0.0302403975705183,	0.0297816946173711},
//        {0.0898336084243552,	0.0705101747358161,	0.074569259798522,	0.109732990329372,	0.0883525391717286,	0.103556439576949,	0.0925878598542966,	0.0761840534461249,	0.0669017792143657,	0.0489158738210138,	0.0385938496178579,	0.0344935443696538,	0.0334236995614277}    };
    
    vector<vector<double>> LVols = {
        {0.0298901076999479,	0.0384618485729838,	0.035406615890827,	0.0172792932214848,	0.0359269090153614,	0.030554344282253,	0.0433452233185514,	0.0127871847274633,	0.0001,	0.004851095418617,	0.011376763478804,	0.0144448684292077,	0.0162794524367493},
        {0.0269430277912836,	0.0475171896986954,	0.038943651917762,	0.0132707319229793,	0.0495236360678772,	0.0430567242416597,	0.0001,	0.0001,	0.0001,	0.00603828344184934,	0.0120044161739736,	0.0153952961991295,	0.0174424478391285},
        {0.1590523704653,	0.0563569513730382,	0.0652387594383946,	0.0001,	0.0461946335971244,	0.0519262121353905,	0.0229265147705421,	0.0100351962992712,	0.022619396809487,	0.00851198631524946,	0.0127640394577317,	0.0162667350004958,	0.018482119820987},
        {0.0385821605231427,	0.129607515362566,	0.0859964937326522,	0.0753331295585729,	0.0687910028192817,	0.0593010303376042,	0.0100048648334645,	0.000316611499441062,	0.0398435667995756,	0.0114965665824287,	0.0137587722339318,	0.0171412972275417,	0.0194560831050069},
        {0.0752637295763275,	0.0480479040742678,	0.0903820210691202,	0.0441392552827633,	0.0863240815718229,	0.0671142697839543,	0.0001,	0.0001,	0.0202231933472448,	0.0144485395424257,	0.0150383436751503,	0.0180815186611317,	0.0204104736865608},
        {0.0548626827700094,	0.0893975538111774,	0.0986070572540404,	0.0001,	0.0799136245666668,	0.0749412611420503,	0.0001,	0.0001,	0.0127039069541703,	0.0176094701436422,	0.0166155621114515,	0.0191328470708967,	0.0213821748929843},
        {0.0589013042955277,	0.0662692076117758,	0.0812096742936898,	0.0383518865289209,	0.0931433196683157,	0.0817931680937065,	0.0203006965689609,	0.00271068023732394,	0.0475125703321655,	0.0212339149840427,	0.0184795450818476,	0.0203256976018442,	0.0224001236421871},
        {0.0636496764884925,	0.0579161480730543,	0.0733783870056938,	0.0680773102851999,	0.0888271230336367,	0.0869538127208891,	0.0436945206847571,	0.063333737151615,	0.0439611368157128,	0.0250237264846706,	0.0206046896084673,	0.0216774330505956,	0.0234861648032244},
        {0.0522059785174914,	0.0683942508439093,	0.0821554530354654,	0.228950102821111,	0.0892027562648573,	0.090971319829463,	0.143152047196689,	0.160163191273443,	0.0433646448979189,	0.0286650727259476,	0.0229573853437557,	0.0231943391073961,	0.0246557131331725},
        {0.0608311946054609,	0.0716651370032551,	0.0845861200600487,	0.0678450174639621,	0.0935631876596218,	0.0943563262861901,	0.0997020611698261,	0.0756932344299434,	0.0482179265850116,	0.0322005041711915,	0.0255010730657548,	0.0248735594429859,	0.0259183630785633},
        {0.0679347855277304,	0.0722668001665007,	0.0851453911404942,	0.0962232517717161,	0.0921632423223607,	0.0967017988430001,	0.0910029841650847,	0.0707715191820247,	0.0533285706624198,	0.0357782112844825,	0.0281987133138467,	0.0267049406491103,	0.0272785162855725},
        {0.074067384870818,	0.0711838032034236,	0.0829481448396004,	0.115936864899812,	0.0900283619209204,	0.0979474407761384,	0.088849589401046,	0.0704145183044169,	0.0575334269059045,	0.0394315301407384,	0.0310128240759117,	0.0286727605555189,	0.0287360542175969},
        {0.0799190069586387,	0.0690883425469676,	0.0766346432042973,	0.0602246749240916,	0.088585257153209,	0.0984883051395202,	0.0882690310114783,	0.0712862050471421,	0.060914494563504,	0.0430909100146623,	0.0339048956087977,	0.030757341389734,	0.0302870574534913},
        {0.086185345050265,	0.0674046480055377,	0.0711607607465756,	0.116092582981825,	0.0839210946820578,	0.0987140254540716,	0.0882412278897139,	0.0726244236660807,	0.0637607065609577,	0.0466609290561837,	0.0368358886285958,	0.0329365592823275,	0.0319245575314352}
    };
    
    // Local Volatility Object
    shared_ptr<LocalVolatility> LV( new LocalVolatility(Maturities, Strikes, LVols));
    
    // Generalised Black Scholes Process with Local Volatility
    shared_ptr<BSLocalVolatilityProcess> bslvprocess(new BSLocalVolatilityProcess(Price, Rate - Rho, LV));
    
    // Pricing Engine
    shared_ptr<FDEuropeanLVEngine> fdlvEngine(new FDEuropeanLVEngine(bslvprocess, Rate, 250, 3201));
    shared_ptr<MCEuropeanEngine> mcEngine(new MCEuropeanEngine(bslvprocess, Rate));
    
    // Products
    shared_ptr<VanillaPayoff> vanillaPayoff(new VanillaPayoff());
    shared_ptr<VanillaOption> vanillaOption(new VanillaOption());
    vanillaOption->setPayoff(vanillaPayoff);
    
    ifstream inputfile;
    inputfile.open("/Users/josh/Documents/optionInputs.txt", ios::in);
    string line;
    if (inputfile.good())
    {
        double Strike, Time;
        char Type;
        
        while(!inputfile.eof())
        {
            // Input file has the data structure as "Type Strike Maturity"
            inputfile >> Type >> Strike >> Time;
            vanillaPayoff->SetStrike(Strike);
            vanillaPayoff->SetType(Type == 'C' ? VanillaPayoff::Call : VanillaPayoff::Put);
            vanillaOption->setExercise(Time);
            vanillaOption->setPricingEngine(fdlvEngine);
            
            printf(Type == 'C' ? "Call Option " : "Put  Option ");
            printf("Strike : %8.5f ", Strike);
            printf("Time : %8.5f ", Time);
            printf("Price(FD) : %8.5f\n", vanillaOption->getValue());
        }
    }
    
    inputfile.close();
    
    return 0;
}