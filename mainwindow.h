#pragma once
#include <QStackedWidget>
#include <QProgressBar>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QStatusBar>
#include <QMainWindow>
#include <QFileSystemModel>
#include <QSortFilterProxyModel>
#include <QListView>
#include <QTreeView>
#include <QSplitter>
#include <QHeaderView>
#include <QTableView>
#include <QTreeView>
#include <QInputDialog>
#include <QLabel>
#include <QDockWidget>
#include <QToolBar>
#include <QTextEdit>
#include <QVariant>
#include <functional>
#include "WorkerThread.h"
#include "ModelView.h"
#include "Console.h"
class MainWindow : public QMainWindow
{
	Q_OBJECT

public:

	MainWindow();
	virtual ~MainWindow();

public slots:

	void dialogSetBoxGeometry();
	void dialogAddMesh();
	void dialogSetConversionFactor();
	void dialogSetDefaultDilation();
	void dialogSaveResults();
	void addMeshByName(const char* name) { _modelMeshFiles.addMesh(name); }
    void processNodes();    
	void mainNodeSelected(const QModelIndex& index);
	void mainShowResults();
    void closeEvent(QCloseEvent *event);
	void menuContextNode(const QPoint &pos);
	void processNodesDone();	
	void saveScreenshot();
	void updateWindowTitle();
	void aboutThisApp();

private:

	NodeModel		_modelMeshFiles;
    GLView*			_viewBox;
	QTreeView*      _viewMeshFiles;
	ModelView*		_viewModel;
	QProgressBar*	_progressWidget;
	QToolBar*       _toolMain;
	WorkerThread*	_threadWorker;
	Console*		_console;
	QStackedWidget*	_stack;

	// actions
	QAction*		_actStop;
	QAction*		_actExit;
	QAction*		_actAddFile;
	QAction*        _actProcess;
	QAction*        _actClear;
	QAction*		_actSetBoxGeometry;
	QAction*		_actShowResults;
	QAction*		_actSaveScreenshot;
	QAction*		_actSaveResults;
	QAction*		_actSetConversionFactor;
	QAction*		_actSetDefaultDilationValue;

	QAction*		_actToggleScaleImages;
	QAction*		_actToggleUseLighting;

	// specific actions that work on the current _currMeshIndex
	QModelIndex     _currMeshIndex;
	QAction*        _actMeshRemove;
	QAction*        _actMeshScale;

	// for box geometry dialog
	float			_conversionFactor;
    std::function<void (void)> _execAfterWorkerFinished;

	void createMeshList();
	void createActions();
	void createMenusAndToolbars();
	void createStatusBar();
	void createStack();

    void startWorker(WorkerThread::Task task, QVariant arg = QVariant());

private slots:

	void removeCurrentNode();
	void scaleCurrentMesh();
    void setLighting(bool lighting_enable);
};
