// -*- Mode: C++; tab-width: 2; -*-
// vi: set ts=2:
//

#include <BALL/CONCEPT/classTest.h>
#include <BALLTestConfig.h>

///////////////////////////
#include <BALL/FORMAT/resourceFile.h>
///////////////////////////

START_TEST(ResourceFile)

/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
using namespace BALL;

ResourceEntry* re;
CHECK(ResourceEntry::ResourceEntry())
	re = new ResourceEntry;
	TEST_NOT_EQUAL(re, 0)
RESULT

CHECK(ResourceEntry::~ResourceEntry())
	delete re;
RESULT

CHECK(ResourceEntry::ResourceEntry(const String&, const String&, ResourceEntry*))
	ResourceEntry R("TEST1", "TEST1");
	ResourceEntry Q("TEST2", "TEST2", &R);
RESULT

CHECK(ResourceEntry::getKey())
	ResourceEntry R("TEST1", "test1");
	TEST_EQUAL(R.getKey(), "TEST1")

	ResourceEntry Q("", "");
	TEST_EQUAL(Q.getKey(), "")
RESULT

CHECK(ResourceEntry::getValue())
	ResourceEntry R("TEST1", "test1");
TEST_EQUAL(R.getValue(), "test1")

ResourceEntry Q("TEST2", "");
	TEST_EQUAL(Q.getValue(), "")
RESULT

CHECK(ResourceEntry::getValue() const)
	const ResourceEntry R("TEST1", "test1");
TEST_EQUAL(R.getValue(), "test1")

const ResourceEntry Q("TEST2", "");
	TEST_EQUAL(Q.getValue(), "")
RESULT

CHECK(ResourceEntry::setValue())
	ResourceEntry R("TEST1", "test1");
	TEST_EQUAL(R.getValue(), "test1");
	R.setValue("test2");
	TEST_EQUAL(R.getValue(), "test2");
	R.setValue("");
	TEST_EQUAL(R.getValue(), "");
RESULT

CHECK(ResourceEntry:countChildren() const)
	ResourceEntry R("TEST1", "test1");
	TEST_EQUAL(R.countChildren(), 0)
RESULT


CHECK(ResourceEntry::insertChild(ResourceEntry&, bool))
	ResourceEntry R("TEST1", "test1");
	TEST_EQUAL(R.countChildren(), 0)

	ResourceEntry& S = *new ResourceEntry("TEST2", "test2");
	R.insertChild(S);
	TEST_EQUAL(R.countChildren(), 1)
	TEST_EQUAL(S.countChildren(), 0)

	ResourceEntry& T = *new ResourceEntry("TEST3", "test3");
	R.insertChild(T);
	TEST_EQUAL(R.countChildren(), 2)
	TEST_EQUAL(S.countChildren(), 0)
	TEST_EQUAL(T.countChildren(), 0)

	ResourceEntry& U = *new ResourceEntry("TEST4", "test4");
	S.insertChild(U);
	TEST_EQUAL(R.countChildren(), 2)
	TEST_EQUAL(S.countChildren(), 1)
	TEST_EQUAL(T.countChildren(), 0)
	TEST_EQUAL(U.countChildren(), 0)
RESULT

CHECK(ResourceEntry::getChild(Position Index))
	ResourceEntry R("TEST1", "test1");
	ResourceEntry& S = *new ResourceEntry("TEST2", "test2");
	ResourceEntry& T = *new ResourceEntry("TEST3", "test3");
	ResourceEntry& U = *new ResourceEntry("TEST4", "test4");
	ResourceEntry& V = *new ResourceEntry("TEST5", "test5");
	R.insertChild(S);
	R.insertChild(T);
	R.insertChild(U);
	R.insertChild(V);
	TEST_EQUAL(R.getChild(0), &S);
	TEST_EQUAL(R.getChild(1), &T);
	TEST_EQUAL(R.getChild(2), &U);
	TEST_EQUAL(R.getChild(3), &V);
	TEST_EQUAL(R.getChild(4), 0);
	TEST_EQUAL(R.getChild(5), 0);
RESULT

CHECK(ResourceEntry::getChild(Poition Index) const)
	ResourceEntry R("TEST1", "test1");
	ResourceEntry& S = *new ResourceEntry("TEST2", "test2");
	ResourceEntry& T = *new ResourceEntry("TEST3", "test3");
	ResourceEntry& U = *new ResourceEntry("TEST4", "test4");
	ResourceEntry& V = *new ResourceEntry("TEST5", "test5");
	R.insertChild(S);
	R.insertChild(T);
	R.insertChild(U);
	R.insertChild(V);
	const ResourceEntry& const_R(R);
	TEST_EQUAL(const_R.getChild(0), &S);
	TEST_EQUAL(const_R.getChild(1), &T);
	TEST_EQUAL(const_R.getChild(2), &U);
	TEST_EQUAL(const_R.getChild(3), &V);
	TEST_EQUAL(const_R.getChild(4), 0);
	TEST_EQUAL(const_R.getChild(5), 0);
RESULT

CHECK(ResourceEntry::ResourceEntry(const ResourceEntry&, bool))
	ResourceEntry R("TEST1", "test1");
	ResourceEntry& Q = *new ResourceEntry("TEST2", "test2");
	R.insertChild(Q);

	ResourceEntry S(R);
	TEST_EQUAL(S.getKey(), "TEST1")
	TEST_EQUAL(S.getValue(), "test1")
	TEST_EQUAL(S.countChildren(), 1)
	ResourceEntry* child = S.getChild(0);
	TEST_NOT_EQUAL(child, 0)
	if (child != 0)
	{
		TEST_EQUAL(child->getKey(), "TEST2")
		TEST_EQUAL(child->getValue(), "test2")
	}

	ResourceEntry T(R, false);
	TEST_EQUAL(T.getKey(), "TEST1")
	TEST_EQUAL(T.getValue(), "test1")
	TEST_EQUAL(T.countChildren(), 0)
	child = T.getChild(0);
	TEST_EQUAL(child, 0)
RESULT

CHECK(ResourceEntry::set(const ResourceEntry&, bool))
	ResourceEntry R("TEST1", "test1");
	ResourceEntry S;
	ResourceEntry& T = *new ResourceEntry("TEST2", "test2");
	R.insertChild(T);
	S.set(R);
	TEST_EQUAL(S.getKey(), "TEST1")
	TEST_EQUAL(S.getValue(), "test1")
	TEST_EQUAL(S.countChildren(), 1)
	S.set(R, false);
	TEST_EQUAL(S.getKey(), "TEST1")
	TEST_EQUAL(S.getValue(), "test1")
	TEST_EQUAL(S.countChildren(), 0)
RESULT

CHECK(ResourceEntry::get(ResourceEntry&, bool))
	ResourceEntry R("TEST1", "test1");
	ResourceEntry S;
	ResourceEntry& T = *new ResourceEntry("TEST2", "test2");
	R.insertChild(T);
	R.get(S);
	TEST_EQUAL(S.getKey(), "TEST1")
	TEST_EQUAL(S.getValue(), "test1")
	TEST_EQUAL(S.countChildren(), 1)
	R.get(S, false);
	TEST_EQUAL(S.getKey(), "TEST1")
	TEST_EQUAL(S.getValue(), "test1")
	TEST_EQUAL(S.countChildren(), 0)
RESULT

CHECK(ResourceEntry::operator = (const ResourceEntry&))
	ResourceEntry R("TEST1", "test1");
	ResourceEntry S;
	ResourceEntry& T = *new ResourceEntry("TEST2", "test2");
	R.insertChild(T);
	S = R;
	TEST_EQUAL(S.getKey(), "TEST1")
	TEST_EQUAL(S.getValue(), "test1")
	TEST_EQUAL(S.countChildren(), 1)
RESULT

CHECK(ResourceEntry::getRoot())
	ResourceEntry R("TEST1", "test1");
	ResourceEntry& S = *new ResourceEntry("TEST2", "test2");
	ResourceEntry& T = *new ResourceEntry("TEST3", "test3");
	ResourceEntry& U = *new ResourceEntry("TEST4", "test4");
	ResourceEntry& V = *new ResourceEntry("TEST5", "test5");
	R.insertChild(S);
	R.insertChild(T);
	R.insertChild(U);
	U.insertChild(V);
	TEST_EQUAL(&V.getRoot(), &R)
	TEST_EQUAL(&U.getRoot(), &R)
	TEST_EQUAL(&T.getRoot(), &R)
	TEST_EQUAL(&S.getRoot(), &R)
	TEST_EQUAL(&R.getRoot(), &R)
RESULT

CHECK(ResourceEntry::getRoot() const)
	ResourceEntry R("TEST1", "test1");
	ResourceEntry& S = *new ResourceEntry("TEST2", "test2");
	ResourceEntry& T = *new ResourceEntry("TEST3", "test3");
	ResourceEntry& U = *new ResourceEntry("TEST4", "test4");
	ResourceEntry& V = *new ResourceEntry("TEST5", "test5");
	R.insertChild(S);
	R.insertChild(T);
	R.insertChild(U);
	U.insertChild(V);
	const ResourceEntry& c_R = R;
	const ResourceEntry& c_S = S;
	const ResourceEntry& c_T = T;
	const ResourceEntry& c_U = U;
	const ResourceEntry& c_V = V;
	TEST_EQUAL(&c_V.getRoot(), &R)
	TEST_EQUAL(&c_U.getRoot(), &R)
	TEST_EQUAL(&c_T.getRoot(), &R)
	TEST_EQUAL(&c_S.getRoot(), &R)
	TEST_EQUAL(&c_R.getRoot(), &R)
RESULT

CHECK(ResourceEntry::getParent())
	ResourceEntry R("TEST1", "test1");
	ResourceEntry& S = *new ResourceEntry("TEST2", "test2");
	ResourceEntry& T = *new ResourceEntry("TEST3", "test3");
	ResourceEntry& U = *new ResourceEntry("TEST4", "test4");
	ResourceEntry& V = *new ResourceEntry("TEST5", "test5");
	R.insertChild(S);
	R.insertChild(T);
	R.insertChild(U);
	U.insertChild(V);
	TEST_EQUAL(V.getParent(), &U)
	TEST_EQUAL(U.getParent(), &R)
	TEST_EQUAL(T.getParent(), &R)
	TEST_EQUAL(S.getParent(), &R)
	TEST_EQUAL(R.getParent(), 0)
RESULT

CHECK(ResourceEntry::getParent() const)
	ResourceEntry R("TEST1", "test1");
	ResourceEntry& S = *new ResourceEntry("TEST2", "test2");
	ResourceEntry& T = *new ResourceEntry("TEST3", "test3");
	ResourceEntry& U = *new ResourceEntry("TEST4", "test4");
	ResourceEntry& V = *new ResourceEntry("TEST5", "test5");
	R.insertChild(S);
	R.insertChild(T);
	R.insertChild(U);
	U.insertChild(V);
	const ResourceEntry& c_R = R;
	const ResourceEntry& c_S = S;
	const ResourceEntry& c_T = T;
	const ResourceEntry& c_U = U;
	const ResourceEntry& c_V = V;
	TEST_EQUAL(c_V.getParent(), &U)
	TEST_EQUAL(c_U.getParent(), &R)
	TEST_EQUAL(c_T.getParent(), &R)
	TEST_EQUAL(c_S.getParent(), &R)
	TEST_EQUAL(c_R.getParent(), 0)
RESULT

CHECK(ResourceEntry::getPath() const)
	ResourceEntry R("TEST1", "test1");
	ResourceEntry& S = *new ResourceEntry("TEST2", "test2");
	ResourceEntry& T = *new ResourceEntry("TEST3", "test3");
	ResourceEntry& U = *new ResourceEntry("TEST4", "test4");
	ResourceEntry& V = *new ResourceEntry("TEST5", "test5");
	R.insertChild(S);
	R.insertChild(T);
	R.insertChild(U);
	U.insertChild(V);
	TEST_EQUAL(V.getPath(), "/TEST1/TEST4/TEST5")
	TEST_EQUAL(U.getPath(), "/TEST1/TEST4")
	TEST_EQUAL(T.getPath(), "/TEST1/TEST3")
	TEST_EQUAL(S.getPath(), "/TEST1/TEST2")
	TEST_EQUAL(R.getPath(), "/TEST1")
RESULT

CHECK(ResourceEntry::getEntry(const String& key_path))
	ResourceEntry R("TEST1", "test1");
	ResourceEntry& S = *new ResourceEntry("TEST2", "test2");
	ResourceEntry& T = *new ResourceEntry("TEST3", "test3");
	ResourceEntry& U = *new ResourceEntry("TEST4", "test4");
	ResourceEntry& V = *new ResourceEntry("TEST5", "test5");
	R.insertChild(S);
	R.insertChild(T);
	R.insertChild(U);
	U.insertChild(V);
	TEST_EQUAL(R.getEntry("TEST2"), &S)
	TEST_EQUAL(R.getEntry("TEST3"), &T)
	TEST_EQUAL(R.getEntry("TEST4"), &U)
	TEST_EQUAL(R.getEntry("TEST4/TEST5"), &V)
	TEST_EQUAL(R.getEntry("TEST2/TEST6"), 0)
RESULT

CHECK(ResourceEntry::getEntry(const String&) const)
	ResourceEntry R("TEST1", "test1");
	ResourceEntry& S = *new ResourceEntry("TEST2", "test2");
	ResourceEntry& T = *new ResourceEntry("TEST3", "test3");
	ResourceEntry& U = *new ResourceEntry("TEST4", "test4");
	ResourceEntry& V = *new ResourceEntry("TEST5", "test5");
	R.insertChild(S);
	R.insertChild(T);
	R.insertChild(U);
	U.insertChild(V);
	const ResourceEntry* r_entry_ptr;
	r_entry_ptr = R.getEntry("TEST2");
	TEST_EQUAL(r_entry_ptr, &S)
	r_entry_ptr = R.getEntry("TEST3");
	TEST_EQUAL(r_entry_ptr, &T)
	r_entry_ptr = R.getEntry("TEST4");
	TEST_EQUAL(r_entry_ptr, &U)
	r_entry_ptr = R.getEntry("TEST4/TEST5");
	TEST_EQUAL(r_entry_ptr, &V)
	r_entry_ptr = R.getEntry("TEST2/TEST6");
	TEST_EQUAL(r_entry_ptr, 0)
RESULT

CHECK(ResourceEntry::countDescendants() const)
	//?????
RESULT

CHECK(ResourceEntry::getDepth() const)
	//?????
RESULT

CHECK(ResourceEntry::insertChild(const String&, const String&, bool))
	//?????
RESULT

CHECK(ResourceEntry::insertSibling(const String&, const String&, bool))
	//?????
RESULT

CHECK(ResourceEntry::insert(const String&, constr String&))
	//?????
RESULT

CHECK(ResourceEntry::mergeChildrenOf(ResourceEntry&, bool))
	//?????
RESULT

CHECK(ResourceEntry::removeChild(const String&, ResourceEntry**))
	//?????
RESULT

CHECK(ResourceEntry::removeKey(const String&))
	//?????
RESULT

CHECK(ResourceEntry::clear())
	//?????
RESULT

CHECK(ResourceEntry::destroy())
	//?????
RESULT

CHECK(ResourceEntry::findChild(const String&))
	//?????
RESULT

CHECK(ResourceEntry::findChild(const String&) const)
	//?????
RESULT

CHECK(ResourceEntry::findDescendant(const String&))
	//?????
RESULT

CHECK(ResourceEntry::findDescendant(const String&) const)
	//?????
RESULT

CHECK(ResourceEntry::findEntry(const String&))
	//?????
RESULT

CHECK(ResourceEntry::findEntry(const String&) const)
	//?????
RESULT

CHECK(ResourceEntry::host(Visistor<ResourceEntry>&))
	//?????
RESULT

CHECK(ResourceEntry::hasChild(const String&) const)
	//?????
RESULT

CHECK(ResourceEntry::isEmpty() const)
	//?????
RESULT

CHECK(ResourceEntry::isParentOf(const ResourceEntry&) const)
	//?????
RESULT

CHECK(ResourceEntry::isChildOf(const ResourceEntry&) const)
	//?????
RESULT

CHECK(ResourceEntry::isAncestorOf(const ResourceEntry&) const)
	//?????
RESULT

CHECK(ResourceEntry::isDescendantOf(const ResourceEntry&) const)
	//?????
RESULT

CHECK(ResourceEntry::isRelatedWith(const ResourceEntry&) const)
	//?????
RESULT

CHECK(ResourceEntry::isRoot() const)
	//?????
RESULT

CHECK(ResourceEntry::isValid() const)
	//?????
RESULT

CHECK(ResourceEntry::dump(std::ostream&, Size) const)
	//?????
RESULT

CHECK(ResourceEntry::apply(UnaryProcessor<ResourceEntry>&))
	//?????
RESULT

CHECK(ResourceEntry::applyChildren(UnaryProcessor<ResourceEntry>&))
	//?????
RESULT

CHECK(ResourceFile::ResourceFile())
	//?????
RESULT

CHECK(ResourceFile::ResourceFile(const String&))
	//?????
RESULT

CHECK(ResourceFile::~ResourceFile())
	//?????
RESULT

CHECK(ResourceFile::destroy())
	//?????
RESULT

ResourceFile f;
CHECK(ResourceFile::open(const String&))
	TEST_EQUAL(f.open(BALL_TEST_DATA_PATH(test.db)), true)
	TEST_EQUAL(f.isValid(), true)
	TEST_NOT_EQUAL(f.getEntry("/Node1"), 0)
	TEST_EQUAL(f.getEntry("//Node1"), 0)
	TEST_NOT_EQUAL(f.getEntry("/Node2"), 0)
	TEST_EQUAL(f.getEntry("//Node2"), 0)
	TEST_EQUAL(f.getEntry("/Node3"), 0)
	TEST_NOT_EQUAL(f.getEntry("/Node1/Node1.1"), 0)
	TEST_NOT_EQUAL(f.getEntry("/Node1/Node1.2"), 0)
	TEST_NOT_EQUAL(f.getEntry("/Node1/Node1.3"), 0)
	TEST_NOT_EQUAL(f.getEntry("/Node1/Node1.4"), 0)
	TEST_NOT_EQUAL(f.getEntry("/Node2/Node2.1"), 0)
	TEST_NOT_EQUAL(f.getEntry("/Node2/Node2.2"), 0)
	TEST_NOT_EQUAL(f.getEntry("/Node2/Node2.2/Node2.2.1"), 0)
	TEST_NOT_EQUAL(f.getEntry("/Node2/Node2.2/Node2.2.2"), 0)
	TEST_NOT_EQUAL(f.getEntry("/Node2/Node2.3"), 0)
RESULT

CHECK(operator >> (std::istream&, ResourceFile&))
	//?????
RESULT

CHECK(ResourceFile::close())
	f.close();
	TEST_EQUAL(f.isValid(), true)
RESULT

CHECK(ResourceFile::saveAs(const Entry&, const String&))
	ResourceFile rf;
	rf.open(BALL_TEST_DATA_PATH(test.db));
	TEST_EQUAL(rf.isValid(), true)
	String filename;
	NEW_TMP_FILE(filename);
	rf.saveAs(filename);
RESULT

CHECK(ResourceFile::save(const Entry&))
	//?????
RESULT

CHECK(ResourceFile::save())
	//?????
RESULT

CHECK(ResourceFile::getSize())
	//?????
RESULT

CHECK(ResourceFile::getRoot())
	//?????
RESULT

CHECK(ResourceFile::getRoot() const)
	//?????
RESULT

CHECK(ResourceFile::getEntry(const String&))
	//?????
RESULT

CHECK(ResourceFile::getEntry(const String&) const)
	//?????
RESULT

CHECK(ResourceFile::getValue(const String&))
	//?????
RESULT

CHECK(ResourceFile::getValue(const String&) const)
	//?????
RESULT

CHECK(ResourceFile::insert(const String&, const String&))
	//?????
RESULT

CHECK(ResourceFile::removeKey(const String&))
	//?????
RESULT

CHECK(ResourceFile::hasKey(const String&) const)
	//?????
RESULT

CHECK(ResourceFile::isEmpty(const String&) const)
	//?????
RESULT

CHECK(ResourceFile::isValid() const)
	//?????
RESULT

CHECK(ResourceFile::dump(std::ostream, Size depth) const)
	//?????
RESULT

CHECK(ResourceFile::host(Visitor<ResourceFile>&))
	//?????
RESULT

CHECK(ResourceFile::apply(UnaryProcessor<Entry>&))
	//?????
RESULT

CHECK(ResourceFile::applyChildren(UnaryProcessor<Entry>&))
	//?????
RESULT
		
/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
END_TEST
