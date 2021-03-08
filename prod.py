import vk_api, requests, pytube
from moviepy.editor import AudioFileClip
from os import system

def enter(token):
    session = vk_api.VkApi(token = token)
    vk = session.get_api()
    return vk

def upload(title,artist):
    token = input('enter your VK token: ')
    vk = enter(token)
    print('waiting...')
    upload_url = vk.audio.getUploadServer()['upload_url']
    request = requests.post(upload_url, files={'file' : open(title+'.mp3', 'rb')})
    saved_audio = vk.audio.save(server = request.json()['server'], audio = request.json()['audio'], hash = request.json()['hash'], artist = artist, title = title)
    print('UPLOADED 2/2')

def download(url,title):
    try:
        yt = pytube.YouTube(url)
    except BaseException:
        return -1
    else:
        print(yt.title)
        audio = yt.streams.filter(only_audio=True).first()
        audio.download(None,title)
        return 1


def extract_mp3(title):
    audioclip = AudioFileClip(title+".mp4")
    audioclip.write_audiofile(title+'.mp3')
    
def main(url, title, artist):
    valid = download(url, title)
    if (valid == 1):
        extract_mp3(title)
        system("del "+title+".mp4")
        print('UPLOADED 1/2')
        upload(title, artist)
        system("del "+title+".mp3")
    else:
        print('ERROR')
    
    
main(input('video url: '), input('Title: '), input('Artist: '))