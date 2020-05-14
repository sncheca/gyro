/// @file
///	@ingroup 	minexamples
///	@copyright	Copyright 2018 The Min-DevKit Authors. All rights reserved.
///	@license	Use of this source code is governed by the MIT License found in the License.md file.

#include "c74_min.h"

using namespace c74::min;


class beat_random : public object<beat_random> {
public:
    MIN_DESCRIPTION	{ "Bang at random intervals." };
    MIN_TAGS		{ "time" };
    MIN_AUTHOR		{ "Cycling '74" };
    MIN_RELATED		{ "min.beat.pattern, link.beat, metro, tempo, drunk" };

    inlet<>  input			{ this, "(toggle) on/off" };
    inlet<>  specialNumber_in  { this, "(float) a number to be printed with the special message"};
    outlet<> bang_out		{ this, "(bang) triggers at randomized interval" };
    outlet<> interval_out	{ this, "(float) the interval for the current bang" };
    outlet<> special_out        { this, "(message) a special message"};
    float localSpecial;

    argument<number> minimum_arg { this, "minimum", "Initial lower-bound of generated random interval.",
        MIN_ARGUMENT_FUNCTION {
            min = arg;
        }
    };

    argument<number> maximum_arg { this, "maximum", "Initial upper-bound of generated random interval.",
        MIN_ARGUMENT_FUNCTION {
            max = arg;
        }
    };
    
//    argument<number> special_arg { this, "special", "A special argument.",
//        MIN_ARGUMENT_FUNCTION {
//            specialNumber = arg;
//        }
//    };

    timer<> metro { this,
        MIN_FUNCTION {
            auto interval = lib::math::random(min, max);
            special_out.send(float(localSpecial)); //this is odd. I need to understand these data types
            interval_out.send(interval);
            bang_out.send("bang");

            metro.delay(interval);
            return {};
        }
    };


    attribute<number> min { this, "min", 400.0, title {"Minimum Interval"},
        description {"Lower-bound of generated random interval."},
        setter { MIN_FUNCTION {
            UNUSED(this);   // silences compiler warning since we don't access class members
 
            double value = args[0];
            if (value < 1.0)
                value = 1.0;
            return {value};
        }},
        category {"Range"}, order {1}
    };


    attribute<number> max { this, "max", 420.0, title {"Maximum Interval"},
        description {"Upper-bound of generated random interval."},
        setter { MIN_FUNCTION {
            UNUSED(this);   // silences compiler warning since we don't access class members
 
            double value = args[0];
            if (value < 1.0)
                value = 1.0;
            return {value};
        }},
        category {"Range"}, order {2}
    };
    
//    attribute<number> specialNumber { this, "max", 42, title {"special number attribute"},
//       description {"Upper-bound of generated random interval."},
//       setter { MIN_FUNCTION {
//           UNUSED(this);   // silences compiler warning since we don't access class members
//
//           double value = args[0];
//           if (value < 1.0)
//               value = 1.0;
//           return {value};
//       }},
//   };

    attribute<bool> on { this, "on", false, title {"On/Off"},
        description {"Activate the timer."},
        setter { MIN_FUNCTION {
            if (args[0] == true)
                metro.delay(0.0);    // fire the first one straight-away
            else
                metro.stop();
            return args;
        }}
    };
    
    message<> m_number { this, "number", "message for special number",
        MIN_FUNCTION {
            if (inlet == 1)
                localSpecial = args[0];
            return {};
        }
    };

    message<> toggle { this, "int", "Toggle the state of the timer.",
        MIN_FUNCTION {
            on = args[0];
            return {};
        }
    };
    
    //try putting a function here to receive the float. 

};


MIN_EXTERNAL(beat_random);
