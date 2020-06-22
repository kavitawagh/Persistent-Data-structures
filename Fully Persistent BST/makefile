a.out: Simulate_NFA.o Impl_Trie.o Impl_FatNode.o Impl_Version_List.o Impl_Int_DLL.o
		gcc -g Simulate_NFA.o Impl_Trie.o Impl_FatNode.o Impl_Version_List.o Impl_Int_DLL.o -pthread
Simulate_NFA.o: Simulate_NFA.c Trie.h
		gcc -c Simulate_NFA.c Trie.h
Impl_Trie.o: Impl_Trie.c FatNode.h Trie.h Version_List.h
		gcc -c Impl_Trie.c FatNode.h Trie.h Version_List.h
Impl_Version_List.o: Impl_Version_List.c Version_List.h
		gcc -c Impl_Version_List.c Version_List.h
Impl_Int_DLL.o: Impl_Int_DLL.c Int_DLL.h
		gcc -c Impl_Int_DLL.c Int_DLL.h
