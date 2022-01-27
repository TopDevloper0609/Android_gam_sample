// Copyright 2022 Google LLC
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     https://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

/// <summary>
/// Controller for the tab/page switch in the store.
/// It switches pages and tabs when different tabs are clicked;
/// It updates the coin text indicator in the store pages;
/// </summary>
public class StoreController : MonoBehaviour
{
    public GameObject tab;
    public GameObject gasPage;
    public GameObject coinPage;
    public GameObject carPage;
    public GameObject subscriptionPage;
    public Text coinsCount;

    private const int UnselectedTabIndex = 0;
    private const int SelectedTabIndex = 1;
    private int _currentTabIndex;
    private GameObject[] _tabs;
    private List<GameObject> _storePages;

    private void Awake()
    {
        _currentTabIndex = 0;
        _storePages = new List<GameObject>()
            {gasPage, coinPage, carPage, subscriptionPage};
        var tabsCount = tab.transform.childCount;
        _tabs = new GameObject[tabsCount];
        for (var tabIndex = 0; tabIndex < tabsCount; tabIndex++)
        {
            _tabs[tabIndex] = tab.transform.GetChild(tabIndex).gameObject;
        }
    }

    private void OnEnable()
    {
        // Update Coin text when entering the store.
        SetCoinsBasedOnGameData();
        OnSwitchPageTabClicked(_currentTabIndex);
    }

    public void OnSwitchPageTabClicked(int tabIndex)
    {
        _currentTabIndex = tabIndex;
        SetActivePage(_storePages[tabIndex]);
        SetActiveTab(tabIndex);
    }

    private void SetActivePage(GameObject targetPage)
    {
        foreach (var page in _storePages)
        {
            page.SetActive(page.Equals(targetPage));
        }
    }

    private void SetActiveTab(int targetTabIndex)
    {
        for (var tabIndex = 0; tabIndex < _tabs.Length; tabIndex++)
        {
            var isTabSelected = tabIndex == targetTabIndex;
            _tabs[tabIndex].transform.GetChild(UnselectedTabIndex).gameObject.SetActive(!isTabSelected);
            _tabs[tabIndex].transform.GetChild(SelectedTabIndex).gameObject.SetActive(isTabSelected);
        }
    }

    // Update coin text in the store page.
    public void SetCoinsBasedOnGameData()
    {
        coinsCount.text = GameDataController.GetGameData().CoinsOwned.ToString();
    }
}