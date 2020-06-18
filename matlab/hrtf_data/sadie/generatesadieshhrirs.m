%{
Copyright 2018 Google Inc. All Rights Reserved.

Modified by Sofia Checa, June 2020 as part of GYRO: a MaxMSP wrapper for
Google Resonance.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS-IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
%}

% Use this script to (re)generate SADIE SH HRIRs.

clearvars
close all
clc

MAX_AMBISONIC_ORDER = 5;
MAX_SUBJECT_ID = 20;
%subjectID = 3;

for subjectID = 1:MAX_SUBJECT_ID

    for order = 1:MAX_AMBISONIC_ORDER
        loadsadie(order, subjectID);
        sadieshhrirs(order, subjectID, 1); %By default, pre-filter for dual-band decoding.
    end
    sadieshhrirstest(subjectID);
end 


