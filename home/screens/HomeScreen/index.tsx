import { StackScreenProps } from '@react-navigation/stack';
import { useCurrentTheme, useExpoTheme } from 'expo-dev-client-components';
import * as React from 'react';
import { SafeAreaView } from 'react-native-safe-area-context';

import { HomeScreenDataQuery } from '../../graphql/types';
import { HomeStackRoutes } from '../../navigation/Navigation.types';
import { useDispatch, useSelector } from '../../redux/Hooks';
import { HistoryList } from '../../types';
import { useAccountName } from '../../utils/AccountNameContext';
import { useInitialData } from '../../utils/InitialDataContext';
import isUserAuthenticated from '../../utils/isUserAuthenticated';
import { HomeScreenView } from './HomeScreenView';

type NavigationProps = StackScreenProps<HomeStackRoutes, 'Home'> & {
  homeScreenData?: Exclude<HomeScreenDataQuery['account']['byName'], null>;
};

export function HomeScreen(props: NavigationProps) {
  const [isFocused, setFocused] = React.useState(true);
  React.useEffect(() => {
    const unsubscribe = props.navigation.addListener('focus', () => {
      setFocused(true);
    });
    const unsubscribeBlur = props.navigation.addListener('blur', () => {
      setFocused(false);
    });

    return () => {
      unsubscribe();
      unsubscribeBlur();
    };
  }, [props.navigation]);

  const dispatch = useDispatch();
  const { recentHistory, allHistory, isAuthenticated } = useSelector(
    React.useCallback((data) => {
      const { history } = data.history;

      return {
        recentHistory: history.take(10) as HistoryList,
        allHistory: history as HistoryList,
        isAuthenticated: isUserAuthenticated(data.session),
      };
    }, [])
  );

  const theme = useExpoTheme();
  const themeType = useCurrentTheme();
  const { accountName } = useAccountName();
  const { homeScreenData } = useInitialData();

  return (
    <SafeAreaView style={{ flex: 1, backgroundColor: theme.background.default }} edges={['top']}>
      <HomeScreenView
        theme={themeType}
        {...props}
        isFocused={isFocused}
        dispatch={dispatch}
        recentHistory={recentHistory}
        allHistory={allHistory}
        accountName={accountName}
        isAuthenticated={isAuthenticated}
        initialData={homeScreenData}
      />
    </SafeAreaView>
  );
}
