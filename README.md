# 大一时期C++期末小项目——基于Qt的本地单线程可视文件持久化型图书管理系统

## 项目背景

- 这是大一**第二学期***选修*的C++入门课的一个*期末项目*（尽管我还是有期末的上机考试）。
- 老师只是让我们写一个简单的控制台程序而已，不过我很早就写完了，因为剩下的时间很多。所以我决定**加点东西**。
- 经过挑选，我最后决定使用**Qt**为我的这个小项目添加*可视化*。
- 这个项目有普通用户和管理员的登录区分，以及普通用户的注册和管理员的新增功能。
- 此外，我还增加了*借阅排名*、通过书名或作者名的*书籍检索*等功能。

## 具体信息说明

- 我是在大二时才开始使用git处理这个项目的，因为我之前还不会git。
- 距离我完成这个项目时间已经有些久了，我只能**尽量回忆**，不敢保证毫无疏漏。
- 另外，由于本项目一开始是命令行项目，大一时的我还是在项目中遗留了一些命令行的遗留代码。
- PS：为了尽量保证**信息全面**，我尝试使用*AI*写具体的介绍，并手动修改。

## CBack 部分

### 项目架构概述

CBack 部分构成了该图书管理系统的核心业务逻辑与数据模型，采用标准的面向对象设计。其核心类通过继承和组合关系构建了一个管理图书、用户及借阅关系的模型。

#### Library 类 (图书馆管理核心)

- **功能**： 作为系统的核心管理类，单例模式运作。统筹管理全馆的书籍 (`bookList`)、用户 (`userList`)，并负责数据的持久化（读取 `readData` / 写入 `writeData`）。
- **主要属性**：
    - `bookList`: 存储所有 `Book` 对象指针的向量。
    - `userList`: 存储所有 `User` (及 `AdminUser`) 对象指针的向量。
    - `rankingList`: 一个映射 (`map`)，用于记录书籍ID和对应的借阅次数，实现借阅排名功能。
    - `NotExistB`, `NotExistU`: 特殊的空对象，用于表示查找书籍或用户失败时的返回值，避免返回 `nullptr`。
    - `pathBookList`, `pathUserList`, `pathRankingList`, `pathAdminList`: 各个数据文件的存储路径。
- **主要方法**：
    - `getBook(getUser)`: 根据ID查找并返回书籍(用户)对象。
    - `addBook(addUser)`: 向系统中添加新的书籍(用户)。
    - `deleteBook(deleteUser)`: 从系统中删除书籍(用户)。
    - `borrowBook`: 处理用户借阅书籍的请求，并更新排名。
    - `returnBook`: 处理用户归还书籍的请求。
    - `renew`: 处理用户续借书籍的请求。
    - `regexSearchTitle(regexSearchAuthor)`: 通过正则表达式对书名或作者名进行模糊搜索。
    - `ranking`: 生成并返回基于 `rankingList` 的借阅排行榜字符串。
    - `displayAllBook`: 返回馆内所有书籍的信息字符串。
    - `readData/writeData`: 从文件加载数据到内存/将内存数据保存至文件，实现了对象的序列化与反序列化。

#### User 类 (用户基类)

- **功能**： 代表系统的普通用户，是所有用户的基类。
- **主要属性**：
    - `uid`: 用户唯一标识。
    - `name`: 用户姓名。
    - `bookList`: 一个向量，存储该用户当前借阅的所有书籍的指针及其对应的到期时间 (`long long` 时间戳)。
- **主要方法**：
    - `borrowBook`: 尝试借阅一本书，内部调用 `Book::lend`。
    - `returnBook`: 归还一本书，计算可能的超时罚金，内部调用 `Book::returnBook`。
    - `renew`: 续借已借阅的书籍。
    - `getMoney`: 计算某本书的超时罚金。
    - `displayFirst`: 返回用户概要信息（如：`"用户 张三 (uid:U12345) 已借阅图书本数：3"`）。
    - `displaySecond`: 返回用户详细的借阅列表信息。

#### AdminUser 类 (管理员用户)

- **功能**： 继承自 `User` 类，代表管理员用户。在系统中与普通用户权限不同（主要通过前端的Qt界面体现），但在数据模型层面，其借阅行为与普通用户一致。
- **主要方法**：
    - 重写了 `displayFirst` 和 `displaySecond` 方法，将输出中的“用户”替换为“管理员”，以实现差异化的信息显示。

#### Book 类 (书籍)

- **功能**： 代表图书馆中的书籍。
- **主要属性**：
    - `uid`: 书籍唯一标识。
    - `title`: 书名。
    - `author`: 作者。
    - `totalCount`: 馆藏总量。
    - `borrowedCount`: 已借出数量。
    - `price`: 价格。
    - `nameList`: 一个向量，存储当前借阅此书籍的所有用户的指针及其借阅时间。
- **主要方法**：
    - `lend`: 执行借阅逻辑，检查库存并更新 `borrowedCount` 和 `nameList`。
    - `returnBook`: 执行还书逻辑，更新 `borrowedCount` 和 `nameList`。
    - `renew`: 执行续借逻辑，修改用户在 `nameList` 中的到期时间。
    - `contains`: 检查某用户是否借阅了此书。
    - `display`: 返回书籍的详细信息字符串。
    - `operator==`: 重载相等运算符，通过UID或书名、作者、价格判断书籍是否相同。

#### Util 类 (工具类)

- **功能**： 提供全局静态工具方法。
- **主要方法**：
    - `getTimeNow`: 获取当前的Unix时间戳（秒）。
    - `processMoney`: 对计算出的罚金字符串进行格式化处理，去除多余的零和小数点。

#### Global 模块 (全局变量)

- **功能**： 通过头文件定义全局变量，方便在程序各处访问核心对象和状态。这是一种简化数据共享的方式。
- **主要全局变量**：
    - `globalLibrary`: 指向当前运行的唯一 `Library` 实例的指针。
    - `globalUser`: 指向当前登录用户的指针。
    - `globalUserUid/globalUserName`: 当前登录用户的ID和姓名。

### 核心交互流程

1.  **借书**：`User::borrowBook` -> `Book::lend` (成功则更新 `Book::borrowedCount`, `Book::nameList`, `User::bookList`, `Library::rankingList`)。
2.  **还书**：`User::returnBook` -> `Book::returnBook` (成功则更新上述列表，并计算罚金)。
3.  **数据持久化**：
    *   **写入**：`Library::writeData` 遍历 `bookList` 和 `userList`，调用 `putBook` 和 `putUser` 将每个对象及其关联关系（借阅记录）转换为特定格式的CSV字符串行，写入对应文件。
    *   **读取**：`Library::readData` 解析文件中的每一行，重建 `Book` 和 `User` 对象。然后通过UID二次查询，将文件中存储的借阅关系重新关联到内存中新创建的对象上，恢复完整的对象图。

### 设计特点

1.  **面向对象**：使用类来封装数据和行为，如 `User`, `Book`, `Library`。
2.  **继承与多态**：`AdminUser` 继承自 `User`，并重写了显示方法。
3.  **关联关系**：`User` 和 `Book` 通过指针向量相互关联，形成多对多关系。
4.  **空对象模式**：使用 `NotExistB` 和 `NotExistU` 避免返回 `nullptr`，增加安全性。
5.  **数据持久化**：自定义文本格式（类CSV）进行序列化，将对象状态保存到文件。
6.  **松耦合的全局访问**：通过 `Global.h` 中的全局变量实现核心组件的便捷访问，与Qt界面层解耦。


## QtClass 部分

### 项目架构概述

#### 界面类结构
- **MainWindow**：应用程序主窗口，负责初始化图书馆和导航
- **SubWidget**：基础界面类，提供通用UI元素和布局
- **LoginWidget**：用户登录界面，继承自SubWidget
- **RegisterWidget**：用户注册界面，继承自SubWidget
- **CommonUserWidget**：普通用户操作界面
- **AdminWidget**：管理员操作界面，继承自CommonUserWidget
- **TempGetMessageWidget**：临时信息获取对话框，继承自SubWidget
- **CheckBook**：书籍信息检查对话框，继承自TempGetMessageWidget
- **ShowInfoDialog**：信息展示对话框

### 类详细说明

#### MainWindow 类
- **功能**：应用程序的主窗口，提供图书馆创建和导航功能
- **主要属性**：
    - centralWidget：中央控件
    - welcomeText：欢迎文本区域
    - libTitle：图书馆名称输入框
    - generateLib：创建图书馆按钮
    - buttonLogin：登录按钮
    - buttonRegister：注册按钮
    - loginWidget：登录界面
    - registerWidget：注册界面
- **主要方法**：
    - closeEvent：处理窗口关闭事件
    - 连接信号与槽，实现界面切换功能

#### SubWidget 类
- **功能**：基础界面类，提供通用UI元素和布局
- **主要属性**：
    - label1, label2：标签控件
    - line1, line2：输入框控件
    - yesButton, cancelButton：按钮控件
    - buttonLayout：按钮布局
    - layoutMain：主布局
    - layoutUid, layoutName：输入框布局
- **主要方法**：
    - getLineOne：获取第一个输入框内容
    - getLineTwo：获取第二个输入框内容
    - deleteTwoLabel：删除第二个标签和输入框

#### LoginWidget 类
- **功能**：用户登录界面，处理用户身份验证
- **主要属性**：
    - commonUserWidget：普通用户界面
    - adminWidget：管理员界面
- **主要方法**：
    - 验证用户凭据
    - 根据用户类型显示相应界面
    - 处理返回信号

#### RegisterWidget 类
- **功能**：用户注册界面，处理新用户注册
- **主要方法**：
    - 收集用户信息
    - 调用后端添加用户功能
    - 处理注册结果

#### CommonUserWidget 类
- **功能**：普通用户操作界面，提供完整的图书管理功能
- **主要属性**：
    - v：按钮数组（8个按钮）
    - leftLayout, rightLayout：左右布局
    - mainLayout：主布局
- **主要方法**：
    - closeEvent：处理窗口关闭事件
    - 实现各种用户功能：
        - 查看用户信息
        - 浏览书籍列表
        - 借阅书籍
        - 归还书籍
        - 续借书籍
        - 查看借阅排名
        - 搜索书籍
        - 退出登录

#### AdminWidget 类
- **功能**：管理员操作界面，提供管理员特有功能
- **主要属性**：
    - v：按钮数组（5个按钮）
    - attachedLayout：附加布局
- **主要方法**：
    - 实现管理员特有功能：
        - 添加用户（普通用户和管理员）
        - 删除用户
        - 添加书籍
        - 删除书籍
        - 查看用户列表

#### TempGetMessageWidget 类
- **功能**：临时信息获取对话框，可自定义标签和按钮
- **主要属性**：
    - point：文本编辑区域
    - first, second：存储的输入内容
- **主要方法**：
    - setLabelOne：设置第一个标签文本
    - setLabelTwo：设置第二个标签文本
    - setTextEdit：设置提示文本
    - getYesButton：获取确定按钮
    - getCancelButton：获取取消按钮

#### CheckBook 类
- **功能**：书籍信息检查对话框，扩展TempGetMessageWidget
- **主要属性**：
    - label：标签数组（3个）
    - line：输入框数组（3个）
    - layout：布局数组（3个）
- **主要方法**：
    - getAuthor：获取作者信息
    - getTotalCount：获取总数量
    - getPrice：获取价格

#### ShowInfoDialog 类
- **功能**：信息展示对话框，显示提醒信息和详细内容
- **主要属性**：
    - yesButton, cancelButton：按钮控件
    - reminder：提醒标签
    - message：信息显示区域
    - v：布局数组（2个）
    - mainLayout：主布局
- **主要方法**：
    - setShowInfo：设置显示的信息内容

### 界面交互流程

1. **启动应用**：显示MainWindow，用户可创建/选择图书馆
2. **登录/注册**：
    - 点击"登录"进入LoginWidget
    - 点击"注册"进入RegisterWidget
3. **用户操作**：
    - 普通用户登录后显示CommonUserWidget
    - 管理员登录后显示AdminWidget
4. **功能操作**：
    - 通过各种对话框(TempGetMessageWidget, CheckBook)获取用户输入
    - 通过ShowInfoDialog显示操作结果和信息
5. **退出应用**：处理数据保存和清理工作

### 设计特点

1. **继承层次清晰**：使用继承减少代码重复，提高可维护性
2. **信号槽机制**：广泛应用Qt的信号槽机制实现界面间通信
3. **全局数据管理**：通过全局变量(globalLibrary, globalUser等)共享数据
4. **异常处理**：使用try-catch块处理可能的异常情况
5. **数据持久化**：在适当时机调用数据写入功能保证数据不丢失
6. **用户友好**：提供丰富的提示信息和确认对话框