#!/usr/bin/env python
# -*- coding: utf-8 -*-

import os
from nose.tools import *
from utilities import execution_path

import mapnik
import pickle

def setup():
    os.chdir(execution_path('.'))

def test_parameter():
    p = mapnik.Parameter('key','value')
    eq_(p[0],'key')
    eq_(p[1],'value')

    p = mapnik.Parameter('int',1)
    eq_(p[0],'int')
    eq_(p[1],1)

    p = mapnik.Parameter('float',1.0777)
    eq_(p[0],'float')
    eq_(p[1],1.0777)


def test_parameters():
    params = mapnik.Parameters()
    p = mapnik.Parameter('float',1.0777)
    eq_(p[0],'float')
    eq_(p[1],1.0777)
    
    params.append(p)
    
    eq_(params[0][0],'float')
    eq_(params[0][1],1.0777)

    eq_(params.get('float'),1.0777)

def test_parameters_pickling():
    params = mapnik.Parameters()
    params.append(mapnik.Parameter('oh',str('yeah')))
    
    params2 = pickle.loads(pickle.dumps(params,pickle.HIGHEST_PROTOCOL))

    eq_(params[0][0],params2[0][0])
    eq_(params[0][1],params2[0][1])
    

if __name__ == "__main__":
    setup()
    [eval(run)() for run in dir() if 'test_' in run]
