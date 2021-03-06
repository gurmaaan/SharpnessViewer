# SharpnessViewer 

**SharpnessViewer** или **"Сортировщик изображений"**, утилита позволяющая: 
  - Просматривать серию изображений
  - Производить вычетание изображений с точной настройкой коэффициента усиления резкости 
  - Рассчитывать критерий резкости для серии изображений и искать самое резкое среди серии
  - Строить график зависимости критерия резкости от номера кадра в серии 
  - Сортировать серию изображения по папкам на резкие и не резкие 


## Описание файлов 

	..\.gitignore - файл исключений для системы контроля версий Git
	..\iconsource.rc - файл для ОС Windows для отображения иконки exe файла изображения при отладке
	..\main.cpp - входная точка в программу 
	..\SharpnessViewer.pro - файл настроек проекта среды Qt 
	..\source.qrc - файл графических и текстовых ресурсов приложения 
	..\static.h - файл текстовых констант используемых в исходном коде 

	..\dialogs - классы оконо 
		..\mainwindow.cpp 
		..\mainwindow.h - главное окно программы
		..\mainwindow.ui

	..\icons\... - папка с иконками программы 
		...
		...

	..\manuals\... - папка с инструкциями и руководствами по применению программы 
	..\manuals\UserManual.pdf

	..\widgets\... - папка с классами кастомных виджетов Qt Designer 
		..\clickablegraphicsscene.cpp  
		..\clickablegraphicsscene.h - собственный класс Графической Сцены предоставляющий функции детектирования нажатий пользвателем кнопок мыши по виджету графического интерфейса
		..\imagewidget.cpp 
		..\imagewidget.h - виджет просмотра серии изображений 
		..\imagewidget.ui
		..\pathwidget.cpp
		..\pathwidget.h - виджет инициализации файлового диалога выбора папки
		..\pathwidget.ui