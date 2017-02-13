#coding=utf-8
import urllib.request
import urllib.parse
import bs4
import time
import base64

class Error(Exception):
    def __init__(self,s):
        self.s=s
    def __str__(self):
        return self.s
    def __repr__(self):
        return self.s


class POJ:
    default_var='''{
    "username":"",
    "password":"",
    "problem":1000
}'''
    
    _status={
        'Waiting':-3,
        'Compiling':-2,
        'Running & Judging':-1,
        'Accepted':0,
        'Wrong Answer':1,
        'Time Limit Exceeded':2,
        'Memory Limit Exceeded':3,
        'Runtime Error':4,
        'Output Limit Exceeded':5,
        'Compile Error':6,
        'Presentation Error':7,
    }
    _restatus={v:k for k,v in _status.items()}
    _last_submit=0
    _FUCK_POJ={
        'User-Agent':'Mozilla/5.0 (Windows NT 6.1; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/45.0.2414.0 Safari/537.36',
        'Referer':'http://poj.org/status',
        'Accept-Language':'zh-CN,zh;q=0.8,en;q=0.6',
        'Content-Type':'application/x-www-form-urlencoded',
    }
    
    def __init__(self,log,config):
        self.username,self.password,self.problem=\
            config['username'],config['password'],config['problem']
        log('Logging in as %s...'%self.username)
        
        cookie=urllib.request.HTTPCookieProcessor()
        self.opener=urllib.request.build_opener(cookie)
        
        result=self.opener.open(urllib.request.Request(
            url='http://poj.org/login',
            data=urllib.parse.urlencode({
                'user_id1':self.username,
                'password1':self.password,
                'B1':'login',
                'url':'/',
            }).encode(),
            headers=self._FUCK_POJ
        )).read()
        if b'Log Out</a>' not in result:
            raise Error('Login failed.')
        else:
            log('Login successful.')

    def _submit(self,log,source):
        delta=self._last_submit+3-time.time()+.1
        if delta>0:
            log('Delaying %.3fs before submitting... '%delta)
            time.sleep(delta)
        
        log('Submitting... ')
        result=self.opener.open(urllib.request.Request(
            url='http://poj.org/submit',
            data=urllib.parse.urlencode({
                'problem_id':self.problem,
                'language':'4',
                'source':base64.b64encode(source.encode()),
                'submit':'Submit',
                'encoded':'1',
            }).encode(),
            headers=self._FUCK_POJ
        )).read()
        if b'Problem Status List</font>' not in result:
            try:
                response=bs4.BeautifulSoup(result)
                delay=float(response.find('font',attrs={'size':'5'}).text\
                    .partition('ms')[0].rpartition(' ')[2])
                raise Error('WARNING: Required to delay %.2fs.'%delay)
            except:
                print(result)###########################
                raise Error('Submit failed.')
        else:
            self._last_submit=time.time()

    def _query(self,log):
        log('Querying...')
        response=bs4.BeautifulSoup(self.opener.open(urllib.request.Request(
            url='http://poj.org/status?problem_id={p}&user_id={u}&language=4'\
                .format(p=self.problem,u=self.username),
            headers=self._FUCK_POJ)).read(),'html5lib')
        try:
            return self._status[response.find(attrs={'class':'in'})\
                    .nextSibling.nextSibling.find('font').text.strip()]
        except:
            try:
                delay=float(response.find('font',attrs={'size':'5'}).text\
                    .partition('ms')[0].rpartition(' ')[2])
                raise Error('WARNING: Required to delay %.2fs.'%delay)
            except:
                raise Error('Query failed.')

    def update(self,log,source):
        self._submit(log,source)
        log('Submitted.')
        for _ in range(20):
            time.sleep(1)
            result=self._query(log)
            log(self._restatus[result])
            if result>=0:
                return
        raise Error('Timeout.')


class Hust:
    default_var='''{
"username":"",
"password":"",
"problem":1000,
"url":"http://www.lydsy.com/JudgeOnline/"
}'''
    
    _last_submit=0
    
    def __init__(self,log,config):
        self.username,self.password,self.problem,self.url=\
            config['username'],config['password'],config['problem'],config['url']
        if self.url.endswith('/'):
            self.url=self.url[:-1]
        if '://' not in self.url:
            self.url='http://'+self.url
        log('Logging in as %s... '%self.username)
        
        cookie=urllib.request.HTTPCookieProcessor()
        self.opener=urllib.request.build_opener(cookie)
        
        result=self.opener.open(urllib.request.Request(
            url='%s/login.php'%self.url,
            data=urllib.parse.urlencode({
                'user_id':self.username,
                'password':self.password,
                'submit':'Submit',
            }).encode(),
        )).read()
        if b'history.go(-2);' not in result:
            raise Error('Login failed.')
        else:
            #set language
            self.opener.open(urllib.request.Request(
                url='%s/setlang.php?lang=cn'%self.url,
            ))
            log('Login successful.')

    def _submit(self,log,source):
        delta=self._last_submit+10-time.time()+.05
        if delta>0:
            log('Delay %.2fs before submitting...'%delta)
            time.sleep(delta)
        
        log('Submitting...')
        result=self.opener.open(urllib.request.Request(
            url='%s/submit.php'%self.url,
            data=urllib.parse.urlencode({
                'id':self.problem,
                'language':'1',
                'source':source,
            }).encode(),
        )).read()
        if b'<form id=simform action="status.php" method="get">' not in result:
            raise Error('Submit failed.')
        else:
            self._last_submit=time.time()
            log('Submitted.')

    def _query(self,log):
        def _proc(s):
            if '编译错' in s:
                raise Error('Compile Error')
            elif '答案错' in s:
                raise Error('Wrong Answer')
            elif '格式' in s:
                raise Error('Presentation Error')
            elif '时间' in s:
                raise Error('Time Limit Exceeded')
            elif '内存' in s:
                raise Error('Memory Limit Exceeded')
            elif '输出' in s:
                raise Error('Output Limit Exceeded')
            elif '正确' in s:
                raise Error('Accepted')
            elif '运行错' in s:
                raise Error('Runtime Error')
            elif '等' in s:
                return 'Waiting...'
            elif '中' in s:
                return 'Compiling...'
            elif '运行并' in s:
                return 'Running & Judging...'
            else:
                raise Error('Unknown status: %s'%s)
        
        log('Querying...')
        response=bs4.BeautifulSoup(self.opener.open(urllib.request.Request(
            url='{url}/status.php?problem_id={p}&user_id={u}&language=1&jresult=-1'\
                .format(url=self.url,p=self.problem,u=self.username),
            )).read(),'html5lib')
        try:
            return _proc(response.findAll('tbody')[-1].\
                find(lambda x:x.name=='tr' and ((not x.has_attr('class')) or x['class']!=['toprow']))\
                .findAll('td')[3].text)
        except Exception as e:
            if isinstance(e,Error):
                raise
            else:
                raise Error('Query failed.')

    def update(self,log,source):
        self._submit(log,source)
        for _ in range(40):
            time.sleep(1)
            log(self._query(log))
        raise Error('Timeout.')


valid_ojs={
    'POJ':POJ,
    'HustOJ':Hust,
}

