#include "NKThreading/NkThread.h"
#include "NKThreading/NkMutex.h"
#include "NKTime/NkChrono.h"
#include "NKWindow/NkMain.h"
#include <iostream>

using namespace nkentseu;
using namespace nkentseu::threading;
/*
// VERSION QUI SE FIGE PAR DEADLOCK
void DeadlockVersion() {
    NkMutex m1;
    NkMutex m2;

    NkThread threadA([&m1, &m2]() {
        NkScopedLockMutex lock1(m1); // Prise de m1
        NkChrono::SleepMilliseconds(100);
        NkScopedLockMutex lock2(m2); // Attente de m2
    });

    NkThread threadB([&m1, &m2]() {
        NkScopedLockMutex lock2(m2); // Prise de m2
        NkChrono::SleepMilliseconds(100);
        NkScopedLockMutex lock1(m1); // Attente de m1
    });

    threadA.Join();
    threadB.Join();
}
*/

int nkmain(const nkentseu::NkEntryState &state)
{
    NkMutex m1;
    NkMutex m2;

    std::cout << "Demarrage des fils avec acquisition ordonnee des verrous..." << std::endl;

    NkThread threadA([&m1, &m2]() {
        NkScopedLockMutex lock1(m1);
        NkChrono::SleepMilliseconds(100);
        NkScopedLockMutex lock2(m2);
        std::cout << "Fil A a termine son traitement." << std::endl;
    });

    NkThread threadB([&m1, &m2]() {
        NkScopedLockMutex lock1(m1);
        NkChrono::SleepMilliseconds(100);
        NkScopedLockMutex lock2(m2);
        std::cout << "Fil B a termine son traitement." << std::endl;
    });

    threadA.Join();
    threadB.Join();

    std::cout << "Programme termine avec succes!" << std::endl;

    return 0;
}