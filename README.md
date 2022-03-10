# C/С++

| Файл | Описание |
|:----:|----------|
|[pointer.cpp](https://github.com/alzoi/C/blob/master/pointer.cpp)| Пример передачи данных в функцию по указателю (*) и по указателю на указатель (**) |
|[dl_list.c](https://github.com/alzoi/C/blob/master/dl_list.c)| Циклический двусвязный список |
|[exec.c](https://github.com/alzoi/C/blob/master/exec.c)| Командный интерпретатор |
|[https://proglib.io/p/open-source/](https://proglib.io/p/open-source/)|Как получить опыт и зарабатывать на Open Source проектах|
|[https://benchmarksgame-team.pages.debian.net](https://benchmarksgame-team.pages.debian.net/benchmarksgame/performance/revcomp.html)|Производительность языков программирования |
|[https://idea.popcount.org/epoll](https://idea.popcount.org/2017-02-20-epoll-is-fundamentally-broken-12/)|Мультиплексирование ввода/вывода|
|[https://google.github.io/](https://google.github.io/styleguide/cppguide.html)|Стиль кодирования|

# Установка компилятора
[MinGW-W64 GCC-8.1.0 i686-posix-dwarf](https://sourceforge.net/projects/mingw-w64/files/Toolchains%20targetting%20Win32/Personal%20Builds/mingw-builds/8.1.0/threads-posix/dwarf/)  версия 8.1.0 позволяет корректно отображать значения stl контейнеров в режиме отладки в Visual Studio Code (вектора std::vector и т. д.)  
https://sourceforge.net/projects/mingw-w64/files/  
https://winlibs.com/  
https://github.com/brechtsanders/winlibs_mingw  
[Стабильная версия GCC 10.3.0](https://github.com/brechtsanders/winlibs_mingw/releases/download/10.3.0-12.0.0-8.0.2-r1/winlibs-i686-posix-dwarf-gcc-10.3.0-mingw-w64-8.0.2-r1.7z) при отладке slt контейнеров отображаются только адреса, без значений элементов.

# Руководства
https://en.cppreference.com/  
[C++ Development Setup with g++ and gdb on Windows 10 | VS Code](https://www.youtube.com/watch?v=ABVeAXcRIJg)  
[Книги](https://habr.com/ru/post/191312/)  

# Библиотеки С++
https://en.cppreference.com/w/cpp/links/libs  
https://www.boost.org/

# Курсы по C++
https://youtu.be/YXbrMny86U0  
https://github.com/mtrempoltsev/msu_cpp_lectures  
https://teccxx.neocities.org/mx1/  

# Visual Studio Code
[Цветовая тема Hop Light](https://marketplace.visualstudio.com/items?itemName=bubersson.theme-hop-light)  
[Тема значков файлов Material Icon Theme](https://marketplace.visualstudio.com/items?itemName=PKief.material-icon-theme)  
[Цветовая тема CLion Plus Theme](https://marketplace.visualstudio.com/items?itemName=meisammafi.clion-plus-theme)  


# Производительность программа
[Which programming language is fastest?](https://benchmarksgame-team.pages.debian.net/benchmarksgame/index.html)  
https://github.com/TechEmpower/FrameworkBenchmarks  
https://www.techempower.com/benchmarks/  

# BackEnd C++ of web app
[Building RESTful Web Service Using C++](https://hackernoon.com/building-restful-web-service-using-c-swagger-ui-and-auto-documented-endpoints-mb153udv)  
https://stackoverflow.com/questions/22258589/c-on-the-back-end-of-web-app  
https://github.com/microsoft/cpprestsdk  
[How popular is C++ for making websites/web applications?](https://web.archive.org/web/20170305115144/https://stackoverflow.com/questions/417816/how-popular-is-c-for-making-websites-web-applications)  
[Сервисы RESTful на C++](https://docs.microsoft.com/ru-ru/archive/msdn-magazine/2013/august/c-bringing-restful-services-to-c-developers)  
[Статья по C++ REST SDK](https://medium.com/@ivan.mejia/modern-c-micro-service-implementation-rest-api-b499ffeaf898)  
[cpprestsdk Casablanca от Microsoft](https://github.com/Microsoft/cpprestsdk)  
[Разработка веб-приложений и веб-сервисов на C++](http://artlang.net/post/razrabotka-veb-prilozheniy-veb-servisov-na-c++/)  
[C++ Web Application Framework](https://cpp.libhunt.com/categories/839-web-application-framework)  
[Oat++ An Open Source C++ Web Framework](https://oatpp.io/)  
[high performance application webserver in C/C++](https://stackoverflow.com/questions/6405811/high-performance-application-webserver-in-c-c)  
https://cpp.libhunt.com/oatpp-alternatives  
https://github.com/civetweb/civetweb  
https://github.com/ipkn/crow  
https://github.com/boostorg/beast  
https://github.com/cesanta/mongoose  
[uWebSockets http-сервер и сервер на WebSockets](https://github.com/uNetworking/uWebSockets)  
http://nxweb.org/ru/  
https://www.cpp-vs.com/versus/go-simple-web-server  
[разработка модулей nginx](https://www.evanmiller.org/nginx-modules-guide.html)  
https://github.com/mibamur/nginx-modules-guide/blob/master/small-dev-nginx-modules-guide-RU.md  
https://github.com/tdv/libevent_test_http_srv  
[c++ Web Server Mongoose](https://www.youtube.com/watch?v=PbrLxCO9Gk8&t=278s)  
[Simple REST API in C++ mongocxx](https://www.youtube.com/watch?v=NC7IGLm69Ts&list=PLrkXkAVRoig2fScCYqfdIp1PQ-WMsVbQc&index=38&t=109s)

## BackEnd стек:
1) языки:
	- Node.js
	- Python
	- C#
	- Java
	- PHP
	- Go
	- Ruby
	- C++
2) фреймворки:
	- Express(Node.js)
	- Django (Python)
	- ASP .Net Core (C#)
	- Spring( Java)
	- Laravel (PHP)
	- Golang (Go)
	- Ruby on Rails (Ruby)
	- Oat++, C++ (C++)
3) базы:
	- PostgreSQL
	- SQLite
	- MySQL
	- MS SQL
	- Azure Cloud SQL
	- MongoDB
	- Redis
	- Cassandra
	- AWS
	- Firebase
4) API:
	- RESTfull
	- Swagger - для документирования

# Подборка ссылок по изучению информационных технологий.  
Сервисы для Web-разработки  

Университет открытого исходного кода  
https://github.com/ossu/computer-science  

Видео курсы от Евгения Попова
http://evgeniypopov.com/  

Blogtactics
http://blogtactics.ru/  

Создать сайт бесплатно  
http://nethouse.ru/  
http://ru.wix.com/  

shutterstock.com  
http://www.shutterstock.com/

http://darkside.vc/

Курсы программирования IRBIS-team  
http://irbis-team.com/  

Скачивание файлов с сайтов  
http://ru.savefrom.net/  
http://zasasa.com/ru/  

Владимир Петрович Путенихин  
http://www.zdorovie-sila-arkaima.ru/  

Simple 8-bit Assembler Simulator  
http://schweigi.github.io/assembler-simulator/

Образовательный проект Продлёнка  
http://prodlenka.pro/  

Виртуальные консультанты А-я-яй.ру  
http://iii.ru/  

Сервис проверки HTML разметки  
http://validator.w3.org/  

Анализ скорости web страниц  
https://developers.google.com/speed/pagespeed/insights/  
https://webopulsar.ru/test/  
https://web.archive.org/  
http://www.nxdom.com/  
http://www.123finder.com/  
http://www.dnsg.co.uk/  

Школа программирования  
http://prog-school.ru/  

Learn C the hard way  
http://c.learncodethehardway.org/book/  

Онлайн-семинары от Microsoft по современным IT-технологиям  
http://techdays.ru/  

MSDN  
http://msdn.microsoft.com/ru-ru/  

Регистрация ИП  
http://reg.smart-law.ru/  
http://www.iloveip.ru/  

Онлайн-бухгалтерия для индивидуальных предпринимателей  
https://www.moedelo.org/  

Компьютерные курсы  
http://specialist.ru/  

Видеолекции ведущих лекторов России  
http://lektorium.tv/  

Технопарк MAIL.RU  
https://tech-mail.ru/  

Mikhail Kurnosov  
http://www.mkurnosov.net/  

Школа анализа данных  
https://yandexdataschool.ru/edu-process/courses/  

Основы веб-технологий  
Яндекс Технологии  
http://tech.yandex.ru/  

Новости Яндекса и его сервисов  
http://blog.yandex.ru/all/  

Помощь вебмастеру  
http://help.yandex.ru/webmaster/  
https://edu.expert.yandex.ru/Webmaster/  

Яндекс.Алгоритм  
http://contest.yandex.ru/  

Яндекс.Директ  
http://direct.yandex.ru/  
https://wordstat.yandex.ru/  

Google Webmaster  
https://sites.google.com/site/webmasterhelpforum/ru/  

Google AdWords  
https://google.com/adwords/  

Курсы «Современная криптография» и «Безопасность приложений»  
http://course.secsem.ru/  

Основы Сетей (StartNetworkings)  
http://www.youtube.com/user/startnetworkings?feature=watch  

IBM  
http://www.ibm.com/developerworks/ru/  

МГУ имени М. В. Ломоносова  
http://www.regatta.cs.msu.su/  
http://parallel.ru/  

RSDN  
http://www.rsdn.ru/  

OpenNET  
http://www.opennet.ru/  

ГНУ/Линуксцентр  
http://www.linuxcenter.ru/  

Простые HTTP-серверы  
ibm.com/developerworks/ru/  

Национальный Открытый Университет «ИНТУИТ»  
http://www.intuit.ru/  

Материалы по практикуму для студентов ВМиК МГУ им. М.В. Ломоносова  
http://cmcmsu.no-ip.info/  
https://cmcmsu.info/  

Си/Си++. От дилетанта до профессионала  
http://ermak.cs.nstu.ru/cprog/html/  

Конференция разработчиков высоконагруженных систем  
http://www.highload.ru/

Документация по Linux  
http://linux.yaroslavl.ru/  

Курс «Сетевое программирование в UNIX»  
http://www.youtube.com/watch?v=QMCXeejSxno/  

Документация по Linux  
http://linux.yaroslavl.ru/  

Руководства UNIX-систем  
http://man.sourcentral.org/  

Руководство FreeBSD для разработчиков  
http://www.freebsd.org.ru/developers-handbook/  

Справочник FreeBSD  
http://www.freebsd.org.ua/man/  
http://muff.kiev.ua/menutree/menu-man/  

Руководство по разработке модулей для ядра Linux 2.6  
http://www.rldp.ru/ldp/lkmpg26r/  

Использование свободного, открытого ПО  
http://wiki.val.bmstu.ru/

Проект GNU  
http://www.gnu.org/  

Компилятор GCC
http://gcc.gnu.org/  

Принципы работы современных веб-браузеров  
http://www.html5rocks.com/ru/tutorials/  

Wataru Nishida
http://www.skyfree.org/  

Massachusetts Institute of Technology (MIT - Массачусетский технологический институт)  
http://pdos.csail.mit.edu/6.828/  

The Zoo at Yale University (Зоопарк в Йельском университете)  
http://zoo.cs.yale.edu/classes/  
http://zoo.cs.yale.edu/classes/cs422/2013/lec/l2-hw.shtml/  
http://wiki.osdev.org/  
http://ru.osdev.wikia.com/  

Руководства для разработчиков Intel  
http://www.intel.ru/content/www/ru/ru/processors/  

Блоги Intel  
http://software.intel.com/ru-ru/blogs/  

Документация по разработке ОС  
http://dev64.wordpress.com/  

Основы работы в операционной системе Unix  
http://linux.vt.tpu.ru/  

Программирование на C и C++  
http://cpp.com.ru/  

Документация о Linux
http://www.iakovlev.org/  

Архив Debian  
http://cdimage.debian.org/cdimage/archive/  

Загрузка образов CD/DVD дисков Debian через HTTP/FTP  
http://www.debian.org/CD/http-ftp/  

Архив FreeBSD
ftp://ftp.freebsd.org/pub/FreeBSD/releases/  

Архив ядра Linux  
https://www.kernel.org/pub/linux/kernel/Historic/  

Хостинг
https://fornex.com/  

HighLoad
http://myforce.ru/  

Параллельные вычисления
https://computing.llnl.gov/  

Московский физико-технический институт (МФТИ)  
http://mipt.ru/  
http://cs.mipt.ru/docs/courses/osstud/os.html  
http://edu.dvgups.ru  
http://cs.mipt.ru/docs/comp/  

Computer Science в МФТИ. Ассемблер  
http://web.archive.org/web/20150801005247/http://cs.mipt.ru/fileadmin/assembler/  

Digital Design  
http://frogs.digdes.ru/  

Планета информатики  
http://inf1.info/  

TCP/IP крупным планом  
http://www.soslan.ru/tcp/  

UNIX: учебный курс  
http://www.openspin.org/materials/courses/admin/  

Сетевые операционные системы  
http://education.aspu.ru/view.php?olif=index/  

Блог Gustavo Duarte  
http://duartes.org/gustavo/blog/  

Журнал разработки операционной системы PhantomEx  
http://phantomexos.blogspot.ru/
http://maisvendoo.org/  

Компилятор compilr.com  
https://compilr.com/  

jsFiddle  
http://jsfiddle.net/  

https://github.com/  
http://www.githubarchive.org/  
http://git-scm.com/book/ru/  

Иконка для сайта
http://www.favicon.cc/  
http://www.xiconeditor.com/  
http://realfavicongenerator.net/  
http://image.online-convert.com/  
http://www180.lunapic.com/  
