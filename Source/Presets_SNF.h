/*
  ==============================================================================

    Presets_SNF.h
    Created: 3 May 2023 10:24:42am
    Author:  Mason Self

  ==============================================================================
*/

#pragma once
#include <sos_curve_adjuster/sos_curve_adjuster.h>

namespace CurveAdjuster
{
    struct Preset
    {
        Connector::connectorsCollection hp, lp, amp;
    };

    /*
     Preset data generated from CurveAdjusterEditor::PrintControlPoints
     
     TODO: Normalized coordinates in case the Curve Adjusters need to change size at some point
     */
    struct Presets
    {
        Preset defaultPreset{
            {{{0.000000, 34.000000}, {43.000000, 118.000000}, {175.000000, 175.000000}}},          //hp
            {{{0.000000, 175.000000}, {60.000000, 51.000000}, {175.000000, 0.000000}}},            //lp
            {{{0.000000, 175.000000}, {5.501251, 81.500000}, {89.000000, 80.000000}},              //amp
                {{89.000000, 80.000000}, {158.500000, 80.000000}, {175.000000, 0.000000}}}
        };
        
        Preset lowPassFade{
            {{{0.0f, 175.0f}, {87.510002f, 175.0f}, {175.0f, 175.0f}}},                            //hp
            {{{0.000000, 175.000000}, {103.000000, 103.000000}, {146.000000, 27.000000}},          //lp
                {{146.000000, 27.000000}, {149.000000, 13.000000}, {175.000000, 0.000000}}},
            {{{0.000000, 175.000000}, {1.500000, 28.000000}, {16.000000, 25.000000}},              //amp
                {{16.000000, 25.000000}, {33.000000, 8.000000}, {41.000000, 6.000000}},
                {{41.000000, 6.000000}, {108.010002, 3.000000}, {175.000000, 0.000000}}}
        };
        
        Preset highPassFade{
            {{{0.000000, 0.000000}, {118.000000, 75.000000}, {175.000000, 175.000000}}},           //hp
            {{{0.000000, 0.000000}, {87.510002, 0.000000}, {175.000000, 0.000000}}},               //lp
            {{{0.000000, 175.000000}, {14.000000, 101.500000}, {87.000000, 81.000000}},            //amp
                {{87.000000, 81.000000}, {151.000000, 58.500000}, {175.000000, 0.000000}}}
        };
        
        Preset thinBandPassFade{
            {{{0.000000, 151.000000}, {61.500000, 93.000000}, {168.000000, 30.000000}},            //hp
                {{168.000000, 30.000000}, {173.500000, 30.500000}, {175.000000, 175.000000}}},
            {{{0.000000, 175.000000}, {86.000000, 68.000000}, {175.000000, 0.000000}}},            //lp
            {{{0.000000, 175.000000}, {2.500000, 14.500000}, {10.000000, 4.000000}},
                {{10.000000, 4.000000}, {92.510002, 2.000000}, {175.000000, 0.000000}}}            //amp
        };
        
        Preset djFilter{
            {{{0.000000, 0.000000}, {57.000000, 58.000000}, {57.000000, 122.000000}},              //hp
                {{57.000000, 122.000000}, {73.510002, 148.000000}, {90.000000, 174.000000}},
                {{90.000000, 174.000000}, {132.509995, 174.500000}, {175.000000, 175.000000}}},
            {{{0.000000, 0.000000}, {44.009998, 0.500000}, {88.000000, 1.000000}},                 //lp
                {{88.000000, 1.000000}, {131.509995, 88.000000}, {175.000000, 175.000000}}},
            {{{0.000000, 175.000000}, {2.510000, 88.000000}, {5.000000, 1.000000}},                //amp
                {{5.000000, 1.000000}, {87.510002, 1.000000}, {170.000000, 1.000000}},
                {{170.000000, 1.000000}, {172.509995, 88.000000}, {175.000000, 175.000000}}}
        };
        
        Preset stairSteps{
            {{{0.000000, 175.000000}, {10.447500, 175.000000}, {20.875000, 175.000000}},           //hp
                {{20.875000, 175.000000}, {21.385000, 162.500000}, {21.875000, 150.000000}},
                {{21.875000, 150.000000}, {32.322498, 150.000000}, {42.750000, 150.000000}},
                {{42.750000, 150.000000}, {43.259998, 137.500000}, {43.750000, 125.000000}},
                {{43.750000, 125.000000}, {54.197498, 125.000000}, {64.625000, 125.000000}},
                {{64.625000, 125.000000}, {65.135002, 112.500000}, {65.625000, 100.000000}},
                {{65.625000, 100.000000}, {76.072502, 100.000000}, {86.500000, 100.000000}},
                {{86.500000, 100.000000}, {87.010002, 87.500000}, {87.500000, 75.000000}},
                {{87.500000, 75.000000}, {97.947502, 75.000000}, {108.375000, 75.000000}},
                {{108.375000, 75.000000}, {108.885002, 62.500000}, {109.375000, 50.000000}},
                {{109.375000, 50.000000}, {119.822502, 50.000000}, {130.250000, 50.000000}},
                {{130.250000, 50.000000}, {130.759995, 37.500000}, {131.250000, 25.000000}},
                {{131.250000, 25.000000}, {141.697495, 25.000000}, {152.125000, 25.000000}},
                {{152.125000, 25.000000}, {175.000000, 25.000000}, {175.000000, 175.000000}}},
            {{{0.000000, 175.000000}, {10.447500, 175.000000}, {20.875000, 175.000000}},           //lp
                {{20.875000, 175.000000}, {21.385000, 162.500000}, {21.875000, 150.000000}},
                {{21.875000, 150.000000}, {32.322498, 150.000000}, {42.750000, 150.000000}},
                {{42.750000, 150.000000}, {43.259998, 137.500000}, {43.750000, 125.000000}},
                {{43.750000, 125.000000}, {54.197498, 125.000000}, {64.625000, 125.000000}},
                {{64.625000, 125.000000}, {65.135002, 112.500000}, {65.625000, 100.000000}},
                {{65.625000, 100.000000}, {76.072502, 100.000000}, {86.500000, 100.000000}},
                {{86.500000, 100.000000}, {87.010002, 87.500000}, {87.500000, 75.000000}},
                {{87.500000, 75.000000}, {97.947502, 75.000000}, {108.375000, 75.000000}},
                {{108.375000, 75.000000}, {108.885002, 62.500000}, {109.375000, 50.000000}},
                {{109.375000, 50.000000}, {119.822502, 50.000000}, {130.250000, 50.000000}},
                {{130.250000, 50.000000}, {130.759995, 37.500000}, {131.250000, 25.000000}},
                {{131.250000, 25.000000}, {141.697495, 25.000000}, {152.125000, 25.000000}},
                {{152.125000, 25.000000}, {152.634995, 12.500000}, {153.125000, 0.000000}},
                {{153.125000, 0.000000}, {164.072495, 0.000000}, {175.000000, 0.000000}}},
            {{{0.000000, 0.000000}, {58.333332, 0.000000}, {175.000000, 0.000000}}}                //amp
        };

            Preset spikes {
                {{{0.000000, 175.000000}, {6.010000, 174.500000}, {12.000000, 174.000000}},        //hp
                    {{12.000000, 174.000000}, {17.000000, 141.000000}, {17.000000, 14.000000}},
                    {{17.000000, 14.000000}, {17.000000, 141.000000}, {22.000000, 173.000000}},
                    {{22.000000, 173.000000}, {37.009998, 173.500000}, {52.000000, 174.000000}},
                    {{52.000000, 174.000000}, {52.490002, 167.000000}, {53.000000, 60.000000}},
                    {{53.000000, 60.000000}, {53.000000, 135.000000}, {62.000000, 174.000000}},
                    {{62.000000, 174.000000}, {79.510002, 174.000000}, {97.000000, 174.000000}},
                    {{97.000000, 174.000000}, {100.000000, 155.000000}, {100.000000, 35.000000}},
                    {{100.000000, 35.000000}, {100.000000, 146.000000}, {106.000000, 174.000000}},
                    {{106.000000, 174.000000}, {124.510002, 174.000000}, {143.000000, 174.000000}},
                    {{143.000000, 174.000000}, {147.000000, 140.000000}, {147.000000, 3.000000}},
                    {{147.000000, 3.000000}, {147.000000, 145.000000}, {152.000000, 174.000000}},
                    {{152.000000, 174.000000}, {163.509995, 174.500000}, {175.000000, 175.000000}}},
                {{{0.000000, 0.000000}, {14.510000, 0.500000}, {29.000000, 1.000000}},              //lp
                    {{29.000000, 1.000000}, {33.000000, 27.000000}, {33.000000, 85.000000}},
                    {{33.000000, 85.000000}, {33.490002, 43.000000}, {34.000000, 1.000000}},
                    {{34.000000, 1.000000}, {51.509998, 1.000000}, {69.000000, 1.000000}},
                    {{69.000000, 1.000000}, {72.000000, 35.000000}, {72.000000, 174.000000}},
                    {{72.000000, 174.000000}, {72.000000, 29.000000}, {73.000000, 1.000000}},
                    {{73.000000, 1.000000}, {89.510002, 1.000000}, {106.000000, 1.000000}},
                    {{106.000000, 1.000000}, {110.000000, 1.000000}, {111.000000, 119.000000}},
                    {{111.000000, 119.000000}, {112.500000, 5.500000}, {115.000000, 1.000000}},
                    {{115.000000, 1.000000}, {136.009995, 1.000000}, {157.000000, 1.000000}},
                    {{157.000000, 1.000000}, {157.490005, 14.000000}, {158.000000, 91.000000}},
                    {{158.000000, 91.000000}, {159.000000, 15.000000}, {161.000000, 2.000000}},
                    {{161.000000, 2.000000}, {168.009995, 1.000000}, {175.000000, 0.000000}}},
                {{{0.000000, 0.000000}, {18.010000, 0.500000}, {36.000000, 1.000000}},               //amp
                {{36.000000, 1.000000}, {42.500000, 33.000000}, {44.000000, 174.000000}},
                {{44.000000, 174.000000}, {44.000000, 28.000000}, {45.000000, 1.000000}},
                {{45.000000, 1.000000}, {62.509998, 1.000000}, {80.000000, 1.000000}},
                {{80.000000, 1.000000}, {85.000000, 45.000000}, {85.000000, 174.000000}},
                {{85.000000, 174.000000}, {85.989998, 87.500000}, {87.000000, 1.000000}},
                {{87.000000, 1.000000}, {106.010002, 0.500000}, {125.000000, 0.000000}},
                {{125.000000, 0.000000}, {131.000000, 51.000000}, {131.000000, 172.000000}},
                {{131.000000, 172.000000}, {131.000000, 40.000000}, {134.000000, 1.000000}},
                {{134.000000, 1.000000}, {154.509995, 0.500000}, {175.000000, 0.000000}}}
            };
        
        Preset wubBi {
            {{{0.000000, 175.000000}, {171.0, 175.000000}, {175.000000, 175.000000}}},               //hp
            {{{0.000000, 175.000000}, {43.509998, 87.500000}, {87.000000, 0.000000}},                //lp
                {{87.000000, 0.000000}, {131.009995, 87.500000}, {175.000000, 175.000000}}},
            {{{0.000000, 175.000000}, {0.000000, 52.500000}, {54.000000, 1.000000}},                 //amp
                {{54.000000, 1.000000}, {90.010002, 1.000000}, {126.000008, 1.000000}},
                {{126.000008, 1.000000}, {173.500000, 55.500000}, {175.000000, 175.000000}}}
        };
        
        Preset yara {
            {{{0.000000, 0.000000}, {10.447500, 0.000000}, {20.875000, 0.000000}},                   //hp
                {{20.875000, 0.000000}, {21.385000, 12.500000}, {21.875000, 25.000000}},
                {{21.875000, 25.000000}, {32.322498, 25.000000}, {42.750000, 25.000000}},
                {{42.750000, 25.000000}, {43.259998, 37.500000}, {43.750000, 50.000000}},
                {{43.750000, 50.000000}, {54.197498, 50.000000}, {64.625000, 50.000000}},
                {{64.625000, 50.000000}, {65.135002, 62.500000}, {65.625000, 75.000000}},
                {{65.625000, 75.000000}, {76.072502, 75.000000}, {86.500000, 75.000000}},
                {{86.500000, 75.000000}, {87.010002, 87.500000}, {87.500000, 100.000000}},
                {{87.500000, 100.000000}, {97.947502, 100.000000}, {108.375000, 100.000000}},
                {{108.375000, 100.000000}, {108.885002, 112.500000}, {109.375000, 125.000000}},
                {{109.375000, 125.000000}, {119.822502, 125.000000}, {130.250000, 125.000000}},
                {{130.250000, 125.000000}, {130.759995, 137.500000}, {131.250000, 150.000000}},
                {{131.250000, 150.000000}, {141.697495, 150.000000}, {152.125000, 150.000000}},
                {{152.125000, 150.000000}, {152.634995, 162.500000}, {153.125000, 175.000000}},
                {{153.125000, 175.000000}, {164.072495, 175.000000}, {175.000000, 175.000000}}},
            {{{0.000000, 0.000000}, {38.000000, -0.000000}, {38.000000, 48.999992}},                  //lp
                {{38.000000, 48.999992}, {38.000000, 21.000000}, {80.000000, 21.000000}},
                {{80.000000, 21.000000}, {85.000000, 21.000000}, {85.000000, 57.000000}},
                {{85.000000, 57.000000}, {85.000000, 19.000000}, {94.000000, 19.000000}},
                {{94.000000, 19.000000}, {102.010002, 29.500000}, {110.000008, 40.000000}},
                {{110.000008, 40.000000}, {112.010002, 22.500000}, {114.000000, 5.000000}},
                {{114.000000, 5.000000}, {120.000000, 42.000000}, {120.000000, 124.000000}},
                {{120.000000, 124.000000}, {120.000000, 23.000000}, {130.000000, 19.000000}},
                {{130.000000, 19.000000}, {138.509995, 92.500000}, {147.000000, 166.000000}},
                {{147.000000, 166.000000}, {148.000000, 84.000000}, {148.000000, 42.000000}},
                {{148.000000, 42.000000}, {171.000000, 42.000000}, {175.000000, 0.000000}}},
            {{{0.000000, 175.000000}, {0.000000, 45.239254}, {16.207050, 45.239254}},                 //amp
                {{16.207050, 45.239254}, {17.207050, 58.100891}, {17.755566, 70.962524}},
                {{17.755566, 70.962524}, {23.465170, 37.231220}, {29.154776, 3.499918}},
                {{29.154776, 3.499918}, {34.195782, 35.000000}, {34.195782, 117.075813}},
                {{34.195782, 117.075813}, {36.141346, 92.772430}, {38.066917, 68.469055}},
                {{38.066917, 68.469055}, {41.701778, 103.782768}, {45.316643, 139.096481}},
                {{45.316643, 139.096481}, {64.009872, 115.000000}, {64.009872, 13.551945}},
                {{64.009872, 13.551945}, {65.983170, 27.164215}, {67.936485, 40.776482}},
                {{67.936485, 40.776482}, {69.821617, 64.700508}, {71.686745, 88.624535}},
                {{71.686745, 88.624535}, {72.473572, 114.187592}, {72.973572, 139.750641}},
                {{72.973572, 139.750641}, {79.682762, 126.799286}, {86.371956, 113.847946}},
                {{86.371956, 113.847946}, {88.642357, 124.853729}, {90.892761, 135.859497}},
                {{90.892761, 135.859497}, {90.892761, 76.000000}, {92.861809, 3.585189}},
                {{92.861809, 3.585189}, {94.900826, 49.493725}, {96.919830, 95.402260}},
                {{96.919830, 95.402260}, {102.212158, 75.831223}, {107.484482, 56.260185}},
                {{107.484482, 56.260185}, {111.971733, 40.188778}, {116.438972, 24.117373}},
                {{116.438972, 24.117373}, {120.075325, 44.116261}, {123.691681, 64.115150}},
                {{123.691681, 64.115150}, {124.329582, 35.162300}, {124.829582, 6.209452}},
                {{124.829582, 6.209452}, {128.018158, 74.000000}, {128.018158, 153.961380}},
                {{128.018158, 153.961380}, {130.661880, 136.548080}, {133.285614, 119.134773}},
                {{133.285614, 119.134773}, {133.785614, 77.043671}, {133.965424, 34.952572}},
                {{133.965424, 34.952572}, {134.465424, 86.031998}, {134.933823, 137.111420}},
                {{134.933823, 137.111420}, {134.933823, 78.140640}, {149.461197, 78.140640}},
                {{149.461197, 78.140640}, {149.461197, 42.000000}, {152.263000, 26.684725}},
                {{152.263000, 26.684725}, {153.589310, 68.633392}, {154.895615, 110.582062}},
                {{154.895615, 110.582062}, {155.395615, 79.227814}, {155.607758, 47.873562}},
                {{155.607758, 47.873562}, {160.488846, 47.873562}, {160.488846, 129.999176}},
                {{160.488846, 129.999176}, {160.488846, 175.000000}, {175.000000, 175.000000}}}
        };
        
        Preset dropOut{
            {{{0.000000, 175.000000}, {32.509998, 174.500000}, {65.000000, 174.000000}},              //hp
                {{65.000000, 174.000000}, {72.489998, 87.500000}, {80.000000, 1.000000}},
                {{80.000000, 1.000000}, {89.010002, 29.000000}, {98.000000, 57.000000}},
                {{98.000000, 57.000000}, {99.500000, 173.000000}, {106.000000, 174.000000}},
                {{106.000000, 174.000000}, {140.509995, 174.500000}, {175.000000, 175.000000}}},
            {{{0.000000, 0.000000}, {39.009998, 0.500000}, {78.000000, 1.000000}},                    //lp
                {{78.000000, 1.000000}, {78.489998, 87.500000}, {79.000000, 174.000000}},
                {{79.000000, 174.000000}, {89.010002, 174.500000}, {99.000000, 175.000000}},
                {{99.000000, 175.000000}, {103.000000, 174.500000}, {103.000000, 1.000000}},
                {{103.000000, 1.000000}, {139.009995, 0.500000}, {175.000000, 0.000000}}},
            {{{0.000000, 0.000000}, {38.510002, 0.500000}, {77.000000, 1.000000}},                    //amp
                {{77.000000, 1.000000}, {78.489998, 87.000000}, {80.000000, 173.000000}},
                {{80.000000, 173.000000}, {89.510002, 135.000000}, {99.000000, 97.000000}},
                {{99.000000, 97.000000}, {99.489998, 49.000000}, {100.000000, 1.000000}},
                {{100.000000, 1.000000}, {137.509995, 0.500000}, {175.000000, 0.000000}}}
            
        };
        
        Preset microBumpsKyleHarris{
            {{{0.000000, 175.000000}, {22.510000, 159.000000}, {45.000000, 143.000000}},              //hp
                {{45.000000, 143.000000}, {48.509998, 111.000000}, {52.000000, 79.000000}},
                {{52.000000, 79.000000}, {73.000000, 73.000000}, {93.000000, 11.000000}},
                {{93.000000, 11.000000}, {103.510002, 42.500000}, {114.000000, 74.000000}},
                {{114.000000, 74.000000}, {123.010002, 52.000000}, {132.000000, 30.000000}},
                {{132.000000, 30.000000}, {153.509995, 28.000000}, {175.000000, 26.000000}}},
            {{{0.000000, 175.000000}, {9.510000, 94.500000}, {19.000000, 14.000000}},                 //lp
                {{19.000000, 14.000000}, {28.010000, 27.000000}, {37.000000, 40.000000}},
                {{37.000000, 40.000000}, {49.009998, 20.500000}, {61.000000, 1.000000}},
                {{61.000000, 1.000000}, {87.010002, 27.500000}, {113.000000, 54.000000}},
                {{113.000000, 54.000000}, {144.009995, 27.000000}, {175.000000, 0.000000}}},
            {{{0.000000, 175.000000}, {44.009998, 148.000000}, {88.000000, 121.000000}},              //amp
                {{88.000000, 121.000000}, {131.509995, 60.500000}, {175.000000, 0.000000}}}
        };
           
        
        std::vector<Preset> states {defaultPreset, lowPassFade, highPassFade, thinBandPassFade, djFilter, stairSteps, spikes, dropOut, wubBi, yara, microBumpsKyleHarris};
    };
}