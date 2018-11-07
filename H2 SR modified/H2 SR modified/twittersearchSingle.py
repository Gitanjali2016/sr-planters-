#Posting a picture to twitter using tweepy
import sys
import tweepy
import os
import datetime

CONSUMER_KEY = 'MKIRveas5hT00MRVxh81YUbg1'
CONSUMER_SECRET = 'zOhmQ8z4lD5uhrn61UxljNwb6JMIAXxzfIPPUbqwCuq2Dce3mL'
ACCESS_KEY = '343801715-1BEVZwYaGuQxHwpKyEbRaSC2y6bvNVyoZ5qQA8Kt'
ACCESS_SECRET = 'JXEisz4wb5G70eDYdlVskcf2aThrLzrGBJ7VQ8BRPfxNf'
auth = tweepy.OAuthHandler(CONSUMER_KEY, CONSUMER_SECRET)
auth.secure = True
auth.set_access_token(ACCESS_KEY, ACCESS_SECRET)
# access the Twitter API using tweepy with OAuth
api = tweepy.API(auth)
counter = 0
#print(api.me().name)

searchTerm = sys.argv[1]
keyword_list = [searchTerm]
#keyword_list = ["donate"]
#print keyword_list
try:
    search_results = api.search(q=keyword_list, count=1)
    result = str(search_results[0].created_at)
    # for i in search_results:
    #     print str(counter) + ": " + str(search_results[counter].created_at)
    #     print str(counter) + ": " + str(search_results[counter].text.encode('utf-8'))
    #     counter = counter + 1
    # result = counter

except tweepy.error.TweepError:
    result = 0
    #print "Problem"
print result
