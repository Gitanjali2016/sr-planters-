import tweepy
import csv
#import pandas as pd
####input your credentials here
consumer_key = '8mh6Lmj8C3Scqtyb9ClI2bu28'
consumer_secret = 'A5vGeamUE68bWUllD5Z4kx2ddiHaaRUcGWsijnunvP5W4Amb92'
access_token = '1027798144589881344-2R13pJvgT7qsoOuMV9hgnpYKY9c6rb'
access_token_secret = '2M8uP0Ju25aBqxnrGRdzMcJGyjOmxqbxPpYX4TnrS5L13'

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
            print("new tweet")
        prevTweet = tweet.text
        print("old tweet")
        #time.sleep(5)
    #print(tweet.created_at, tweet.text)
    #csvWriter.writerow([tweet.created_at, tweet.text.encode('utf-8')])

