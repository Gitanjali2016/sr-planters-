import tweepy
import csv
#import pandas as pd
####input your credentials here
consumer_key = ''
consumer_secret = ''
access_token = ''
access_token_secret = ''

auth = tweepy.OAuthHandler(consumer_key, consumer_secret)
auth.set_access_token(access_token, access_token_secret)
api = tweepy.API(auth,wait_on_rate_limit=True)
#####United Airlines
# Open/Create a file to append data
#csvFile = open('ua.csv', 'a')
#Use csv Writer
#csvWriter = csv.writer(csvFile)

prevTweet = ""
while True :
    for tweet in tweepy.Cursor(api.search,q="#refugees",count=1,
                           lang="en").items():
    
        if (tweet.text != prevTweet):
            #do things
            print("r")
        prevTweet = tweet.text
    #print(tweet.created_at, tweet.text)
    #csvWriter.writerow([tweet.created_at, tweet.text.encode('utf-8')])

