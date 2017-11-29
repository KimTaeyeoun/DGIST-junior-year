import numpy as np
import pandas as pd


time = input("시간을 입력하세요 (e.g. 11/27 18:00)")


total_number = 680
number_14 = 138
number_15 = 176
number_16 = 168
number_17 = 197
election = pd.read_csv('학생명단.csv', encoding = "ISO-8859-1")

count = election['check'].value_counts()  #1은 모두 투표, 2는 학생회장단만, 3은 학번대표만
try:
	total_count_1 = count.iloc[0] + count.iloc[1]   #학생회장단 총 투표수
	total_rate_1 = (total_count_1 / total_number) * 100
except:
	total_count_1 = count.iloc[0]   #학생회장단 총 투표수
	total_rate_1 = (total_count_1 / total_number) * 100

election_14 = election[:138]
election_15 = election[138:315]
election_16 = election[315:483]
election_17 = election[483:]

count_14 = election_14['check'].value_counts()
count_15 = election_15['check'].value_counts()
count_16 = election_16['check'].value_counts()
count_17 = election_17['check'].value_counts()

try:
	total_count_1_14 = count_14.iloc[0] + count_14.iloc[1]   #학생회장단 14 투표수
	total_rate_1_14 = (total_count_1_14 / number_14) * 100
except:
	total_count_1_14 = count_14.iloc[0]    #학생회장단 14 투표수
	total_rate_1_14 = (total_count_1_14 / number_14) * 100
try:
	total_count_1_15 = count_15.iloc[0] + count_15.iloc[1]   #학생회장단 15 투표수
	total_rate_1_15 = (total_count_1_15 / number_15) * 100
except:
	total_count_1_15 = count_15.iloc[0]    #학생회장단 15 투표수
	total_rate_1_15 = (total_count_1_15 / number_15) * 100
try:
	total_count_1_16 = count_16.iloc[0] + count_16.iloc[1]   #학생회장단 16 투표수
	total_rate_1_16 = (total_count_1_16 / number_16) * 100
except:
	total_count_1_16 = count_16.iloc[0]   #학생회장단 16 투표수
	total_rate_1_16 = (total_count_1_16 / number_16) * 100
try:
	total_count_1_17 = count_17.iloc[0] + count_17.iloc[1]   #학생회장단 17 투표수
	total_rate_1_17 = (total_count_1_17 / number_17) * 100
except:
	total_count_1_17 = count_17.iloc[0]   #학생회장단 17 투표수
	total_rate_1_17 = (total_count_1_17 / number_17) * 100
"""
try:
    total_count_2_17 = count_17.iloc[0] + count_17.iloc[2]   #학번대표 17 투표수
    total_rate_2_17 = (total_count_2_17 / number_17) * 100
except:
    total_count_2_17 = count_17.iloc[0]   #학번대표 14 투표수
    total_rate_2_17 = (total_count_2_17 / number_17) * 100
try:    
    total_count_2_15 = count_15.iloc[0] + count_15.iloc[2]   #학번대표 15 투표수
    total_rate_2_15 = (total_count_2_15 / number_15) * 100
except:
    total_count_2_15 = count_15.iloc[0]    #학번대표 15 투표수
    total_rate_2_15 = (total_count_2_15 / number_15) * 100
try:
    total_count_2_16 = count_16.iloc[0] + count_16.iloc[2]   #학번대표 16 투표수
    total_rate_2_16 = (total_count_2_16 / number_16) * 100
except:
    total_count_2_16 = count_16.iloc[0]    #학번대표 16 투표수
    total_rate_2_16 = (total_count_2_16 / number_16) * 100
"""
    
a = pd.Series({'투표':'학생회장단 선거 총 투표율', '투표율':total_rate_1})
b = pd.Series({'투표':'학생회장단 선거 14학번 투표율', '투표율':total_rate_1_14})
c = pd.Series({'투표':'학생회장단 선거 15학번 투표율', '투표율':total_rate_1_15})
d = pd.Series({'투표':'학생회장단 선거 16학번 투표율', '투표율':total_rate_1_16})
e = pd.Series({'투표':'학생회장단 선거 17학번 투표율', '투표율':total_rate_1_17})
##f = pd.Series({'투표':'15학번대표 투표율', '투표율':total_rate_2_15})
##g = pd.Series({'투표':'16학번대표 투표율', '투표율':total_rate_2_16})
##h = pd.Series({'투표':'17학번대표 투표율', '투표율':total_rate_2_17})
election_rate = pd.DataFrame([a, b, c, d, e])
election_rate.index = election_rate['투표']
election_rate = election_rate.drop(['투표'], axis = 1)
election_rate.index.name = None
   