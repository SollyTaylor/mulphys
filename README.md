# Mulphys

### 功能定位

Mulphys的基本定位是多物理场技术的工程软件。

- 多物理场问题的发生位置——物理场的交界面。
  - 多物理场的耦合很多情况下都发生在物理场的界面上，因而重点强化了几何表面上场的处理。
- 多物理场问题的数据来源（DataSource）
  - 基于几何直接求解
    - 高超声速压力场
    - 流线积分热流场
    - 基于射线模型的方向场等
  - 基于偏微分方程的导出解
    - CFD求解结果
    - 有限元求解的表面位移场
    - 电磁分析后表面电流分布

### 应用场景

多物理场有如下典型的使用场景：

- 对于飞行器整体分析，可以融合的流固热燃控红外电磁等多学科耦合仿真
- 外部流场解的融合应用，将现有的多学科物理场的求解结果提取出来后，在界面上进行耦合分析
- 将耦合后的应用用于仿真对象的实时与准实时求解
- 与内部和外部的控制器的支持

### 几何工具支持

- （Rebuilder）原始CAD几何的逆向与网格重构、包面功能（将外部多种输入归一化为单一的可以调节几何表面稠密度的几何，为后面网格稀疏化做准备）
- （Coarsener）网格稀疏化（提升实时解算速度，需要进行网格稀疏化无关性验证）
- （Mapper）同源网格映射（同源网格物理场的映射功能、单一几何分离成多个几何后物理场的继承获取功能）
  - 飞行器在高空分离后，A=>B+C，B和C都是A的子集，B和C都会通过映射获取A的物理场的解
  - 气动热流线积分求解时，流线和表面几何网格是两个不同的几何场，此时二者需要进行网格映射

### 模型界定

1. 具有多个同源的几何场，可以有多个相互之间可以实现同源网格映射的几何场（Mapper），可以发生变形，但是不能分裂。区分多个物理场的情况往往是因为问题涉及了多物理场耦合问题，多个物理场可以共享几何也可以分别保存于同源异构的几何上，重要的示例如下：
   * 表面物理场和流线积分场之间是同源的几何场，二者之间存在数据映射
   * 流固耦合物理场而言，流体场和结构场之间可以有两种处理方式，1. 存储在同一个几何上实现共享几何的物理场映射，2. 存储在同源异构几何上通过插值实现几何场映射；
2. 几何场上的最小处理单元是几何片段，场处理器可以处理一个、几个几何片段（例如舵面偏动）和全部的几何片段，所以场处理器运行前配置中主要指定片段索引，未指定则会处理全部几何片段。在处理局部几何片段前，物理场应该已经存在，例如几何法线场处理器会在几何舵面偏动后计算，但几何法线场在最开始就已经存在。
3. 场处理器可以接受多个几何场，同时可以更新多个几何场（append、generate、participate），为了实现求解依序进行，场处理器之间需要进行流水线编排(Processor Composer)，然后将场处理器形成的依赖有向无环图（Dependency DAG）线性化形成可以直接运行的流畅流水线
4. ​

![](./designs/designs.png)

###模型功能特性

1. 几何场GeometricalField（下称gf）和处理流水线（processor、dynamics、model）是独立存在的，模型的流水线可以配置好后，注入gf
2. gf包含了仿真过程中的所有信息，gf可以随时启停，持久化后还可以继续进行仿真试验
3. 模型的服务模式：脚本模式（Script-Driven）、交互模式（Interaction-Driver）
4. 多模型独立运行且模型之间使用（同源网格映射器Mapper实施）物理场映射
   1. 多分辨率的模型，需要定义状态映射Mapper、分阶段仿真过程中状态交换
5. ​



### 数据源与场处理器特性

1. ​
2. （DataSource）数据源适配多种数据库，根据数据库读写效率提供不同支持
3. （DataPoint）数据点适配多种物理解用于高维空间点插值
4. （DataCoordinate）数据坐标与数据点进行映射
5. （DataInterpolator）数据插值器



### 代码模型

#### 运行几何读取

| 主体   | 输入1            | 输入2                    | 输出                    | 动作 |
| ------ | ---------------- | ------------------------ | ----------------------- | ---- |
| reader | reader名称字符串 | 各种类型几何文件所在路径 | panax的Json格式几何文件 | read |
|        | cgns             | /path/to/xxxx.cgns       | xxx.geom.mphs           |      |

* 实例：

  ```
  reader r = new reader("cgns")
  geometry g = r.read("/path/to/xxxx.cgns")
  ```



#### 运行几何转换写出（writer）



#### 运行求解器（solver）



processes

* file -> reader -> geometry
* geometry -> writer -> file
* geometry [, field, environment]   -> solver -> field
* field (init) -> dynamics -> field

runner

* model(dynamics1[,dynmiacs2...]) + reporter
* batch + model(dynamics1[,dynmiacs2...]) + reporter
* controller + model(dynamics1[,dynmiacs2...]) + reporter

simulation

* runner1 -> runner2 -> ... ->runnerN
* scheduler


！！！！！！！！

场的处理直接使用armadillo实现，所有元素直接作为mat出现，mat可以转换为scalar和vector

！！！！！！！！


1. 以上每一个对象都需要dump出来，查看其中的详细信息, mulphys dump <object-name>
2. solver不关心变量名称，只关心（1）场变量类型和输入顺序、（2）转换方式是格心格点插值积分、（3）输入输出几何
3. 不考虑边值问题，只考虑初值问题






！！！！！！！！

务必注意分区求解物理场，solver需要接受物理场进行进一步处理

！！！！！！！！









路线图和基本需求

1. 构建内核库，重建resource继承树和geometry类型
2. 实现reader，通过reader读取file生成geometry类型，此类型是可以共享的
3. 代码驱动的配置，全新的Panax语言
4. 支持插件扩展各种组件
5. 支持命令驱动的打包并形成可直接驱动的模型包，代码只提取需要的模型和插件模块进行运行
6. 支持多种几何文件的读取并形成统一的基于Json的数据文件，作为统一的数据交换格式，几何格式要开放，可以被其他工具方便使用
7. Json Schema解析处理使用rapidJson，Json本身的处理使用Qt框架
8. 各种组件存在依存关系，模块之间可以作为其他模块的初始化组成部分




命令行

- mphs read foo.txt (根据后缀名决定读取器，如果有多个对应则提示用户显式制定读取器) 输出bar.pnxf文件
- mphs write bar.pnxf foo.plt
- mphs run foo.pnx (执行panax文件)
- mphs describe component_foo (输出component_foo组件的详细信息)
- mphs version
- mphs help
- mphs package (打包panax为一个独立的可执行包)


