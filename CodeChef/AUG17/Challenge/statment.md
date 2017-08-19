# Mathison and the Data Warehouse
After finishing his internship at DeepMind, Mathison has started his own company. Knowing that storing data is probably the most important thing a company should take care of, he decided to manage a data warehouse. DWs are central repositories of integrated data from one or more disparate sources. They store current and historical data in one single place and are used for creating analytical reports for knowledge workers throughout the enterprise (check Wikipedia for more details).

Managing a DWH is not an easy task so Mathison would like you to help him. In this task, you have to implement a simplified version of a data warehouse managing system. A DWH managing system is an interactive application that handles users' requests, stores and retrieves data, buys hard disk drives (HDDs) and much more.

Your application must handle three types of events:

你需要开发一个应用，支持下面三种操作

1. `0 cid q` : Client with id cid wants to store q cells of data.
2. `1 cid p` : Client with id cid wants to retrieve his p-th data-cell.
3. `2 hid` : Hard-disk with id hid has crashed and all data that was stored on it is lost. The hard-disk can still be used in the future!

In order to simplify the problem, you can assume that a client is allowed to store data only once. But he is allowed to query the warehouse as many times as he wants.

每个用户只会存储一次(操作1)， 但是他会查询仓库信息若干次(操作2)

A client will not query the data warehouse if he has no data stored!

用户不会在没有存储数据的情况下进行查询

In order to handle some events, your application can send these types of commands involving storing/retrieving data:

为了解决这些问题， 你的应用可以发送这两种指令存储、获取数据

	s hid pid

This command must follow a client's request to **store** data and means that you store the previous client's data on hard-disk hid, starting at cell pid (0-based indexing) 

这个指令说明你在标号为 hid 的硬盘里从第 pid 格开始存储数据。

For example, you might have a request of form 0 100 10. The client with id 100 wants to store 10 units (cells) of data in our warehouse. Let's assume you have a hard-disk (with id 5). You can respond with a command s 5 120, meaning that you store the client's 100 units of data on only one hard-disk, hdd5 from cell 120 to cell 129. All ids must be valid. You must be careful not to overflow any hdd!

对于用户的需求`0 100 10`, 我们假设你有一个 hid 为 5 的硬盘。你需要回复一个指令 `s 5 120`, 意味着你把这个用户的 `100` 单位数据存在了一个硬盘里，即硬盘 `5`的第 $120$ 到 $129$ 格

**Note** : You can choose not to store the data (a risky move). In this case, you have to print `-1 -1` for hid and pid. No penalty fee will be charged in this case!

你可以选择不存储数据(存在巨大风险), 此时你可以发送`s -1 -1`。不会被计算penalty fee

	i hid pid

This command must follow a client's request to **retrieve** his data. 

这个指令必须在用户读取数据之后发出

For example, let's assume that you had the commands described above and you get a new one `1 100 5`. In this case, we have to respond with `i 5 125` as you stored the data from client 100 on hdd5 and the 5-th cell of data is located on the 125-th cell on hdd5.

紧接着上面那个时间，你收到了一个新指令`1 100 5`, 此时你需要回复`i 5 125`，表示用户 `100` 的第 `5` 格数据保存在硬盘 `5` 的 `125` 格

**Note**: If you do not have the requested data, hid and pid must be equal to -1 (and you will pay a fixed penalty - see input and scoring sections).

如果你没有需要的数据，需要回复 `i -1 - 1`, 你需要付出一个固定的peanlty

**Note**: If you report a false information (i.e. the pid-th cell on the hdd hid doesn't contain the request cell), you will get a WA. Everyone hates fake information!

如果你造了个假新闻，你会收到一个WA !

There are other types of commands that you can use in order to manage the data warehouse:

加下来是你用于管理数据仓库的其他指令

	b t
Buy a new hard-disk of type t. The newly purchased hard-disk will get the next available id starting from zero (the first one you buy will have id 0, the second one will have id 1 and so on).

买一个类型为 `t` 的新硬盘， 这个硬盘有一个从 `0` 开始发放的标号

	cp hid[source] pid[source] q hid[destination] pid[destination]

Copy q cells of data from hard-disk $hid_{source}$, starting at $pid_{source}$, to hard-disk $hid_{destination}$, starting at $pid_{destination}$.

将 $hid_{source}$ 中从 $pid_{source}$ 开始的 $q$ 格数据移动到 $hid_{des}$， 从$pid_{des}$ 开始
## Interactive

This task is interactive. You have to write a program that will interact with a custom judge (i.e. the judge is deterministic but the events you get will depend on your program behaviour).

这是一个交互式任务，你要写一个程序和 custom judge 交互. 你得到的事件会和你程序的行为相关

You have to start by reading the number of events, the number of types of hard-drives and their description (see Input section for more details). This information doesn't depend on your program.

你需要从读入事件和硬盘描述开始(输入格式)

Then you are able to exchange messages with the judge. There are three types of messages:

然后你需要和 judge 交互。 下面有三种指令

	g
If there are still events to handle, you can use this type of message to get a new one. You will get a event of one of the three types described in above.

如果还有更多的需要解决的事件，这个指令会使你获得一个新的

**Note**: If you ask for a new request even if you haven't solved the last one or if there are no more events you will get a WA.

注意到事件需要一一被解决，否则你会获得WA

	p cmd
You can use this type of message to send a command cmd to the judge. The command can have any form described in the statement.

发送一个描述中提到的指令

	end

This message must be sent in order to end the interaction with the judge. If the message is not sent the judge will crash with a WA.

结束交互。

**Note**: Both types of messages must end with a newline ('\n' character).

每个指令都需要以一个`\n`为结尾

**Note**: Don't forget to flush the output buffer (i.e. stdout).
Scoring
Everything has a price!

Hard-disks cost money and they read and write at different speeds (so there are different costs for reading/writing)

不同的硬盘有着不一样的读取速度和代价

Storing and retrieving data also has a price. 

存储和获取数据也有价格

If you store q units of data on a hard-disk that writes data at w units per second the cost of this operation will be q * w.

如果你在一个 `w` 速度的硬盘存储 `q` 单位数据, 代价是 `qw`

If you read q units of data from a hard-disk that reads at speed r units per second, the operation will cost you q * r.

同上

If you do not have some requested data (you didn't store it or you overwrote the cell) you must pay a fixed penalty.

如果你没有某种数据，或者你重写了一格，你需要付出一个固定的penalty

Your score for one test is the sum of costs for all the commands that you make. 

单个测试点得分是所有指令代价的和

The final score is the sum of scores in all tests. The goal is to minimize that score.

总分是所有点得分的和，目标是最小化

If your program works incorrectly on any of the tests, you will get a WA.

Otherwise, you will get AC and your score will be decided by only a fraction of the tests (see test generation). The final score will be revealed after the contest.

否则你就会通过某种算式得分

## Input
The first line of the input file contains two integers, N and H, where N is the number of events and H is the number of types of hard-disks available.

The next H lines will contain 4 integers `p r w c` (separated by spaces), where p is the price associated with this type of hard-disk, c is the capacity (there are c data-cells) and r and w are the reading/writing speeds (costs) or this type.

The next line will one contain integer, penalty, the penalty you pay if you don't have the requested data.

All N events are generated by the judge when they are requested by your program.

## Output
The output file will be your program's interaction with the judge.

**Note**: Please read the constraint on the maximum number of messages!

## Constraints and extra notes

**Note**: Do NOT add extra spaces or tabs in any message or command! You will probably get a WA verdict.

**Note**: You are allowed to send at most POST 40,000 messages.

你发送信息的上限是 40000 条

**Note**: Copying data from a hard-disk to another doesn't affect the source hdd but overwrites the cells in the second one. Only bounds are checked!

**Note**: The judge might return a WA even if a TLE was expected (ex: waiting for a response)

如果TLE了有可能返回WA

**Note**: The judge is NOT adaptive! (i.e. it won't try to purposely generate events to increase your score)

**Note**: All commands are executed in linear time! (ex: a cp command is done in O(q))

所有指令都在线性时间内执行

A message is what you send/receive to/from the judge. A command is an instruction that is contained within a message and is designed to be executed by the DWH managing system!

A unit of data is equal to one cell.

There are 20,000 events (i.e. N = 20,000 for all tests).

每个测试点有恰好 20000 个事件

There are at most 10 types of hard-disks.

最多 10 种硬盘

You can buy at most 1050 hard-disks.

你可以买最多 1050 个硬盘

The price of a hard-disk is an integer between 1 and 200,000

The capacity of a hard-disk is an integer between 1 and 25,000

The reading and writing speeds are integers between 1 and 1000

The penalty is an integer between 50,000 and 700,000

Clients can be uniquely identified by their ids, which are numbers between 1 and 100,000

A client can store at most 1000 data-cells.

A client can store data only once.

A client can ask for his data multiple times.

Everything is 0-based (unless otherwise specified).

You must print -1 -1if you do not have some requested cell! Any other pair of numbers will get you a WA!

A hard-disk can crash multiple times. The data will be erased (and lost) every single time! The hard-disk can be reused after that!

It is guaranteed that for all input files will contain at least one type of hard-disk with capacity at least 10,000.

There are only male clients because the author was too lazy to add 'she' or 'her' all over the statement.

The author would like to apologize for the long statement!
## Test generation
There are 20 tests. For each one of them N, H, the hard-disks' descriptions and the penalty were created 'by hand' (i.e. are not random).

All events are generation on the run (randomly), based on your program.
Each type of hard-disk is a small variation of the below types:

A very cheap hard-disk with low costs for reading and writing but small capacity.

A very expensive hard-disk with low costs for reading and writing and big capacity.

A medium-priced hard-disk with low read (or write) and small-ish capacity (about 100 cells).

Randomly generated (all 4 attributes) hard-disks!

There are several types of datasets:

Events distribution: 20% store, 70% index, 10% crash (4 tests)

Events distribution: 50% store, 45% index, 5% crash (3 tests)

Events distribution: 60% store, 35% index, 5% crash (3 tests)

Events distribution: 70% store, 20% index, 10% crash (3 tests)

Events distribution: 35% store, 50% index, 15% crash (4 tests)

Events distribution: 49% store, 50% index, 1% crash (3 tests)


During the contest, your program will run on 6 tests (one from each category).
## Example
### Input:
```
5 2
100 10 20 2000
50 20 10 2000
30000
```

## Interaction
The user should first read N, H, the description of the hard-disks, and the penalty from standard input (as mentioned in the Input section).

Then, the interaction between the two programs (some message exchanges and the end command) should be:
```
User              Judge
p b 0
p b 1
g
                          0 123 200
p s 0 0
g
                          1 123 55
p i 0 55
p cp 0 9 45 1 10
g
                          2 0
g
                          1 123 0
p i -1 -1
g
                          1 123 12
p i 1 13
end
 ```

## Explanation
The cost for buying the two hard-disks is 100 + 50 = 150.

The store operation is executed on a hard-disk of type 0 and so it costs 20 * 200 = 4000.

The first post operation (the first index) is just a read on a type 0 hdd and so it costs 10.

The second post operations is a copy from a type 0 hdd to a type 1 hdd and so it costs: 10 * 45 (to read) + 10 * 10 (to write) = 450 + 100 = 550.

The crash doesn't cost you a thing! :)

The fourth get will cost you a penalty fee (of 30000) because the 0-th cell was not copied on the second hard-disk and was erased by the crash.

The fifth (and last) get is a read from a type 1 hdd and so it costs 20.

The total score for this test is 150 + 4000 + 10 + 550 + 30000 + 20 = 34730.